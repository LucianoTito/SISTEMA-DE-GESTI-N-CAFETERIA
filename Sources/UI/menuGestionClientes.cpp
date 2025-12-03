#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstdio> // Para sprintf
#include <cstring>

#include "../../Headers/UI/menuGestionClientes.h"
#include "../../Headers/Entities/Cliente.h"
#include "../../Headers/Entities/Pedido.h"
#include "../../Headers/Persistence/ArchivoCliente.h"
#include "../../Headers/Persistence/ArchivoPedido.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Tablas.h"

using namespace std;

// ==========================================
// PROTOTIPOS AUXILIARES (PRIVADOS)
// ==========================================
void listarClientesSubmenu();
void listarClientesGenerico(bool mostrarEliminados);
void listarClientesConMasPedidos();
void listarClientesPorMontoGastado();
void listarClientesOrdenadosApellido();

// Helpers Visuales
void mostrarEncabezadoClientes();
void mostrarFilaCliente(Cliente c);

// Helpers Lógicos
int buscarClienteID(ArchivoCliente& arc, bool buscarEliminados);
Cliente* obtenerClientesActivos(int &cantidad); // Retorna array dinámico

// ==========================================
// MENU PRINCIPAL
// ==========================================
void menuClientes(){
    int opcion;
    while(true){
        limpiarConsola();
        imprimirTituloDecorado("GESTION DE CLIENTES", 94);
        rlutil::setColor(PaletaCafe::CREMA);
        cout << "1. AGREGAR CLIENTE" << endl;
        cout << "2. LISTADOS Y REPORTES" << endl;
        cout << "3. MODIFICAR CLIENTE" << endl;
        cout << "4. ELIMINAR CLIENTE (BAJA)" << endl;
        cout << "5. RECUPERAR CLIENTE (ALTA)" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(94);
        rlutil::setColor(PaletaCafe::ESPUMA);
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaDoble(94);
        restaurarColor();

        opcion = ingresarEntero("SELECCIONE UNA OPCION: ");
        limpiarConsola();

        // Control de pausa para evitar dobles 'enter' al volver de submenús
        bool pausar = true;

        switch(opcion){
            case 1: agregarCliente(); break;
            case 2:
                listarClientesSubmenu();
                pausar = false; // El submenú ya gestiona sus pausas
                break;
            case 3: modificarCliente(); break;
            case 4: bajaCliente(); break;
            case 5: altaCliente(); break;
            case 0: return;
            default: imprimirMensajeError("Opcion incorrecta."); break;
        }
        if(pausar) pausarConsola();
    }
}

// ==========================================
// ABM: ALTA, BAJA, MODIFICACION
// ==========================================

void agregarCliente(){
    ArchivoCliente arcCliente("Clientes.dat");
    Cliente regCliente;
    int nuevoID = arcCliente.contarRegistros() + 1;

    cout << "---------- AGREGAR NUEVO CLIENTE ----------" << endl;
    regCliente.Cargar(nuevoID);

    if (arcCliente.grabarRegistro(regCliente)){
        cout << "Cliente agregado exitosamente." << endl;
    } else {
        cout << "ERROR: No se pudo agregar el cliente." << endl;
    }
}

void modificarCliente(){
    ArchivoCliente arcCliente("Clientes.dat");
    cout << "--------- MODIFICAR CLIENTE ---------" << endl;

    int pos = buscarClienteID(arcCliente, false); // false = buscar activos
    if (pos == -1) return;

    Cliente reg = arcCliente.leerRegistro(pos);

    cout << endl << "Cliente seleccionado:" << endl;
    mostrarEncabezadoClientes();
    mostrarFilaCliente(reg);
    lineaSimple(94);

    cout << "1) Nombre | 2) Apellido | 3) Telefono | 4) Mail | 0) Cancelar" << endl;
    int opc = ingresarEntero("Que desea modificar?: ");

    char aux[50]; // Buffer auxiliar

    switch(opc){
        case 1:
            cargarCadenaObligatoria("Nuevo Nombre: ", "Dato obligatorio", aux, 30);
            reg.setNombre(aux); break;
        case 2:
            cargarCadenaObligatoria("Nuevo Apellido: ", "Dato obligatorio", aux, 30);
            reg.setApellido(aux); break;
        case 3:
            cargarCadenaObligatoria("Nuevo Telefono: ", "Dato obligatorio", aux, 20);
            reg.setTelefono(aux); break;
        case 4:
            cargarCadenaObligatoria("Nuevo Mail: ", "Dato obligatorio", aux, 40);
            reg.setMail(aux); break;
        case 0: return;
        default: cout << "Opcion invalida." << endl; return;
    }

    if (arcCliente.modificarRegistro(reg, pos)){
        cout << "Cliente modificado exitosamente." << endl;
    } else {
        cout << "ERROR al guardar cambios." << endl;
    }
}

void bajaCliente(){
    ArchivoCliente arcCliente("Clientes.dat");
    cout << "---------- ELIMINAR CLIENTE ----------" << endl;

    int pos = buscarClienteID(arcCliente, false);
    if (pos == -1) return;

    Cliente reg = arcCliente.leerRegistro(pos);

    cout << endl << "Va a eliminar:" << endl;
    mostrarEncabezadoClientes();
    mostrarFilaCliente(reg);

    char conf;
    cout << "Confirmar baja? (S/N): "; cin >> conf;

    if (conf == 'S' || conf == 's'){
        reg.setEliminado(true);
        if(arcCliente.modificarRegistro(reg, pos)) {
            rlutil::setColor(PaletaCafe::BASE);
            lineaSimple(94);
            rlutil::setColor(PaletaCafe::CREMA);

            cout << "CLIENTE DADO DE BAJA EXITOSAMENTE" << endl;

            rlutil::setColor(PaletaCafe::BASE);
            lineaSimple(94);
            restaurarColor();

        }
        else imprimirMensajeError("ERROR al eliminar.");
    }
}

void altaCliente(){
    ArchivoCliente arcCliente("Clientes.dat");
    cout << "------- RECUPERAR CLIENTE -------" << endl;

    int pos = buscarClienteID(arcCliente, true); // true = buscar eliminados
    if (pos == -1) return;

    Cliente reg = arcCliente.leerRegistro(pos);

    cout << endl << "Va a recuperar:" << endl;
    mostrarEncabezadoClientes();
    mostrarFilaCliente(reg);

    char conf;
    cout << "Confirmar alta? (S/N): "; cin >> conf;

    if (conf == 'S' || conf == 's'){
        reg.setEliminado(false);
                if(arcCliente.modificarRegistro(reg, pos)) {
            rlutil::setColor(PaletaCafe::BASE);
            lineaSimple(94);
            rlutil::setColor(PaletaCafe::CREMA);
            cout << "CLIENTE DADO DE ALTA EXITOSAMENTE" << endl;
            rlutil::setColor(PaletaCafe::BASE);
            lineaSimple(94);
            restaurarColor();
        }
        else imprimirMensajeError("ERROR al recuperar.");
    }
}

// ==========================================
// SUBMENU LISTADOS
// ==========================================

void listarClientesSubmenu(){
    while(true){
        limpiarConsola();
        imprimirTituloDecorado("REPORTES DE CLIENTES", 94);
        rlutil::setColor(PaletaCafe::CREMA);
        cout << "1. TODOS LOS ACTIVOS" << endl;
        cout << "2. TODOS LOS ELIMINADOS" << endl;
        cout << "3. ORDENADOS POR APELLIDO" << endl;
        cout << "4. RANKING POR CANTIDAD DE PEDIDOS" << endl;
        cout << "5. CLIENTES QUE SUPERAN UN MONTO DE COMPRA" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(94);
        rlutil::setColor(PaletaCafe::ESPUMA);
        cout << "0. VOLVER" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaDoble(94);
        restaurarColor();
        int opc = ingresarEntero("OPCION: ");
        limpiarConsola();

        switch(opc){
            case 1: listarClientesGenerico(false); break;
            case 2: listarClientesGenerico(true); break;
            case 3: listarClientesOrdenadosApellido(); break;
            case 4: listarClientesConMasPedidos(); break;
            case 5: listarClientesPorMontoGastado(); break;
            case 0: return;
            default: imprimirMensajeError("Incorrecto."); break;
        }
        pausarConsola();
    }
}

// ==========================================
// LOGICA DE REPORTES
// ==========================================

void listarClientesGenerico(bool mostrarEliminados){
    ArchivoCliente arc("Clientes.dat");
    if(!arc.hayClientesConEstadoEliminado(mostrarEliminados)){
        cout << "No hay clientes " << (mostrarEliminados ? "eliminados" : "activos") << "." << endl; return;
    }

    cout << "LISTADO DE CLIENTES " << (mostrarEliminados ? "(BAJAS)" : "(ACTIVOS)") << endl;
    mostrarEncabezadoClientes();

    int total = arc.contarRegistros();
    for(int i=0; i<total; i++){
        Cliente c = arc.leerRegistro(i);
        if(c.getEliminado() == mostrarEliminados) mostrarFilaCliente(c);
    }
    lineaSimple(94);
}

void listarClientesOrdenadosApellido(){
    int cantidad = 0;
    Cliente* vector = obtenerClientesActivos(cantidad);
    if(vector == nullptr) return;

    // Burbujeo
    for(int i=0; i<cantidad-1; i++){
        for(int j=i+1; j<cantidad; j++){
            if(strcmp(vector[i].getApellido(), vector[j].getApellido()) > 0){
                Cliente aux = vector[i]; vector[i] = vector[j]; vector[j] = aux;
            }
        }
    }

    cout << "CLIENTES ORDENADOS POR APELLIDO" << endl;
    mostrarEncabezadoClientes();
    for(int i=0; i<cantidad; i++) mostrarFilaCliente(vector[i]);
    lineaSimple(94);

    delete[] vector;
}

void listarClientesConMasPedidos(){
    int cantClientes = 0;
    Cliente* clientes = obtenerClientesActivos(cantClientes);
    if(clientes == nullptr) return;

    int* contadores = new int[cantClientes];
    for(int i=0; i<cantClientes; i++) contadores[i] = 0;

    ArchivoPedido arcP("Pedidos.dat");
    int totalPedidos = arcP.contarRegistros();

    for(int i=0; i<totalPedidos; i++){
        Pedido p = arcP.leerRegistro(i);
        if(!p.getEliminado() && p.getIdPedido() != -1){
            for(int k=0; k<cantClientes; k++){
                if(clientes[k].getId() == p.getIdCliente()){
                    contadores[k]++;
                    break;
                }
            }
        }
    }

    // Ordenar
    for(int i=0; i<cantClientes-1; i++){
        for(int j=i+1; j<cantClientes; j++){
            if(contadores[j] > contadores[i]){
                int auxC = contadores[i]; contadores[i] = contadores[j]; contadores[j] = auxC;
                Cliente auxCli = clientes[i]; clientes[i] = clientes[j]; clientes[j] = auxCli;
            }
        }
    }

    cout << "RANKING DE PEDIDOS POR CLIENTE" << endl;
    mostrarEncabezadoClientes();

    bool hubo = false;
    for(int i=0; i<cantClientes; i++){
        if(contadores[i] > 0){
            mostrarFilaCliente(clientes[i]);
            cout << right << setw(92) << "^-- Pedidos: " << contadores[i] << endl;
            lineaSimple(94);
            hubo = true;
        }
    }
    if(!hubo) cout << "No hay pedidos registrados aun." << endl;

    delete[] clientes;
    delete[] contadores;
}

void listarClientesPorMontoGastado(){
    int cantClientes = 0;
    Cliente* clientes = obtenerClientesActivos(cantClientes);
    if(clientes == nullptr) return;

    float montoMinimo = ingresarFloat("Ingrese monto minimo acumulado: $");

    float* acumuladores = new float[cantClientes];
    for(int i=0; i<cantClientes; i++) acumuladores[i] = 0.0f;

    ArchivoPedido arcP("Pedidos.dat");
    int totalPedidos = arcP.contarRegistros();

    for(int i=0; i<totalPedidos; i++){
        Pedido p = arcP.leerRegistro(i);
        if(!p.getEliminado() && p.getIdPedido() != -1){
            for(int k=0; k<cantClientes; k++){
                if(clientes[k].getId() == p.getIdCliente()){
                    acumuladores[k] += p.getTotal();
                    break;
                }
            }
        }
    }

    cout << endl << "CLIENTES CON GASTO SUPERIOR A $" << montoMinimo << endl;
    mostrarEncabezadoClientes();

    bool hubo = false;
    for(int i=0; i<cantClientes; i++){
        if(acumuladores[i] >= montoMinimo){
            mostrarFilaCliente(clientes[i]);
            cout << right << setw(92) << "^-- Total: $" << fixed << setprecision(2) << acumuladores[i] << endl;
            lineaSimple(94);
            hubo = true;
        }
    }
    if(!hubo) cout << "Ningun cliente supera ese monto." << endl;

    delete[] clientes;
    delete[] acumuladores;
}

// ==========================================
// HELPERS
// ==========================================

int buscarClienteID(ArchivoCliente& arc, bool buscarEliminados){
    if (!arc.hayClientesConEstadoEliminado(buscarEliminados)) {
        cout << "No hay clientes " << (buscarEliminados ? "eliminados" : "activos") << "." << endl;
        return -1;
    }

    listarClientesGenerico(buscarEliminados);
    cout << endl;

    int id = ingresarEntero("Ingrese ID Cliente: ");
    int pos = arc.buscarRegistro(id);

    if(pos == -1){
        cout << "ID no encontrado." << endl; return -1;
    }

    Cliente c = arc.leerRegistro(pos);
    if(c.getEliminado() != buscarEliminados){
        cout << "Estado incorrecto para esta operacion." << endl; return -1;
    }
    return pos;
}

Cliente* obtenerClientesActivos(int &cantidad){
    ArchivoCliente arc("Clientes.dat");
    int total = arc.contarRegistros();
    if(total == 0 || !arc.hayClientesConEstadoEliminado(false)){
        cout << "No hay clientes activos." << endl;
        cantidad = 0; return nullptr;
    }

    Cliente* temp = new Cliente[total];
    cantidad = 0;
    for(int i=0; i<total; i++){
        Cliente c = arc.leerRegistro(i);
        if(!c.getEliminado()){
            temp[cantidad] = c;
            cantidad++;
        }
    }
    return temp;
}

void mostrarEncabezadoClientes(){
    lineaDoble(94);
    imprimirFilaCliente("ID", "NOMBRE", "APELLIDO", "TELEFONO", "MAIL");
    lineaSimple(94);
}

void mostrarFilaCliente(Cliente c){
    char sId[10];
    sprintf(sId, "%d", c.getId());
    imprimirFilaCliente(sId, c.getNombre(), c.getApellido(), c.getTelefono(), c.getMail());
}
