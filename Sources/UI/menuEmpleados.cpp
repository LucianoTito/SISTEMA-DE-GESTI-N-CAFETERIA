#include <iostream>
#include <cstdio>
#include <cstring>
#include "../../Headers/UI/menuEmpleados.h"
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/Persistence/ArchivoEmpleado.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Tablas.h"

using namespace std;

// ==========================================
// FUNCIONES AUXILIARES
// ==========================================
void listarEmpleados(bool mostrarEliminados = false);
void altaEmpleado();
void bajaEmpleado();
void recuperarEmpleado();
void modificarEmpleado();
void listarEmpleadosOrdenadosPorApellido();

// Helpers visuales y lógicos
void mostrarEncabezadoEmpleados();
void mostrarFilaEmpleado(Empleado e);
void ordenarEmpleadosPorApellido(Empleado registros[], int cantidad);
int buscarEmpleadoID(ArchivoEmpleado& arc, bool permitirEliminados);

// ==========================================
// MENU PRINCIPAL
// ==========================================
void menuEmpleados() {
    int opcion;
    while (true) {
        limpiarConsola();
        imprimirTituloDecorado("GESTION DE EMPLEADOS", 100);
        rlutil::setColor(PaletaCafe::CREMA);
        cout << "1. AGREGAR EMPLEADO" << endl;
        cout << "2. LISTAR EMPLEADOS ACTIVOS" << endl;
        cout << "3. LISTAR EMPLEADOS DADOS DE BAJA" << endl;
        cout << "4. MODIFICAR EMPLEADO" << endl;
        cout << "5. ELIMINAR EMPLEADO (BAJA)" << endl;
        cout << "6. RECUPERAR EMPLEADO (DAR DE ALTA)" << endl;
        cout << "7. LISTAR ORDENADOS POR APELLIDO" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(100);
        rlutil::setColor(PaletaCafe::ESPUMA);
        cout << "0. VOLVER" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaDoble(100);
        restaurarColor();

        opcion = ingresarEntero("SELECCIONE UNA OPCION: ");

        limpiarConsola();
        switch (opcion) {
            case 1: altaEmpleado(); break;
            case 2: listarEmpleados(false); break; // false = solo activos
            case 3: listarEmpleados(true); break;  // true = solo eliminados
            case 4: modificarEmpleado(); break;
            case 5: bajaEmpleado(); break;
            case 6: recuperarEmpleado(); break;
            case 7: listarEmpleadosOrdenadosPorApellido(); break;
            case 0: return;
            default: imprimirMensajeError("Opcion incorrecta."); break;
        }
        pausarConsola();
    }
}

// ==========================================
// ALTA (AGREGAR)
// ==========================================
void altaEmpleado() {
    ArchivoEmpleado arc("Empleados.dat");
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(100);
    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << "☕ AGREGAR NUEVO EMPLEADO" << endl;
    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(100);
    restaurarColor();

    Empleado nuevoEmpleado;
    int nuevoID = arc.contarRegistros() + 1;

    // Aprovechamos el método Cargar de la clase que ya pide los datos
    nuevoEmpleado.Cargar(nuevoID);

        if (arc.grabarRegistro(nuevoEmpleado)) {
        rlutil::setColor(PaletaCafe::OK);
        cout << endl << ">>> Empleado registrado exitosamente." << endl;
    } else {
        rlutil::setColor(PaletaCafe::ERROR);
        cout << endl << ">>> ERROR: No se pudo guardar el registro." << endl;
    }
    restaurarColor();
}

// ==========================================
// LISTADOS
// ==========================================
void listarEmpleados(bool mostrarEliminados) {
    ArchivoEmpleado arc("Empleados.dat");
    cout << "---------- LISTADO DE EMPLEADOS " << (mostrarEliminados ? "ELIMINADOS" : "ACTIVOS") << " ----------" << endl;

    int cantidad = arc.contarRegistros();
    if (cantidad == 0) {
        cout << "No hay registros en el archivo." << endl; return;
    }

    mostrarEncabezadoEmpleados();

    bool hayRegistros = false;
    for (int i = 0; i < cantidad; i++) {
        Empleado e = arc.leerRegistro(i);
        // Filtramos según lo que pida el parámetro 'mostrarEliminados'
        if (e.getEliminado() == mostrarEliminados) {
            mostrarFilaEmpleado(e);
            hayRegistros = true;
        }
    }
    lineaSimple(118);

    if (!hayRegistros) cout << "No hay empleados " << (mostrarEliminados ? "eliminados" : "activos") << " para mostrar." << endl;
}

void listarEmpleadosOrdenadosPorApellido() {
    ArchivoEmpleado arc("Empleados.dat");
    cout << "---------- LISTADO ORDENADO POR APELLIDO ----------" << endl;

    int total = arc.contarRegistros();
    if (total == 0) { cout << "Sin registros." << endl; return; }

    // Memoria dinámica para cargar todos y ordenar
    Empleado* registros = new Empleado[total];

    // Filtramos solo activos al cargar el vector
    int activos = 0;
    for(int i=0; i<total; i++){
        Empleado e = arc.leerRegistro(i);
        if(!e.getEliminado()){
            registros[activos] = e;
            activos++;
        }
    }

    if (activos == 0) {
        cout << "No hay empleados activos para ordenar." << endl;
        delete[] registros;
        return;
    }

    ordenarEmpleadosPorApellido(registros, activos);

    mostrarEncabezadoEmpleados();
    for(int i=0; i<activos; i++){
        mostrarFilaEmpleado(registros[i]);
    }
    lineaSimple(118);

    delete[] registros;
}

// ==========================================
// BAJA Y RECUPERACION
// ==========================================
void bajaEmpleado() {
    ArchivoEmpleado arc("Empleados.dat");
    cout << "---------- BAJA DE EMPLEADO ----------" << endl;

    // Buscamos solo entre activos (false)
    int pos = buscarEmpleadoID(arc, false);
    if (pos == -1) return;

    Empleado e = arc.leerRegistro(pos);

    cout << endl << "Va a eliminar al siguiente empleado:" << endl;
    mostrarEncabezadoEmpleados();
    mostrarFilaEmpleado(e);
    lineaSimple(118);

    char confirm;
    cout << "Confirmar baja? (S/N): ";
    cin >> confirm;

    if (confirm == 'S' || confirm == 's') {
        e.setEliminado(true);
        if (arc.modificarRegistro(e, pos)) cout << ">>> Empleado dado de baja." << endl;
        else cout << ">>> Error al guardar." << endl;
    }
}

void recuperarEmpleado() { // Punto 6
    ArchivoEmpleado arc("Empleados.dat");
    cout << "---------- RECUPERAR EMPLEADO (ALTA) ----------" << endl;

    // Buscamos solo entre eliminados (true)
    int pos = buscarEmpleadoID(arc, true);
    if (pos == -1) return;

    Empleado e = arc.leerRegistro(pos);

    cout << endl << "Va a reactivar al siguiente empleado:" << endl;
    mostrarEncabezadoEmpleados();
    mostrarFilaEmpleado(e);
    lineaSimple(118);

    char confirm;
    cout << "Confirmar reactivacion? (S/N): ";
    cin >> confirm;

    if (confirm == 'S' || confirm == 's') {
        e.setEliminado(false);
        if (arc.modificarRegistro(e, pos)) cout << ">>> Empleado recuperado exitosamente." << endl;
        else cout << ">>> Error al guardar." << endl;
    }
}

// ==========================================
// MODIFICACION
// ==========================================
void modificarEmpleado() {
    ArchivoEmpleado arc("Empleados.dat");
        rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(100);
    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << "🍮 MODIFICAR EMPLEADO" << endl;
    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(100);
    restaurarColor();

    int pos = buscarEmpleadoID(arc, false);
    if (pos == -1) return;

    Empleado e = arc.leerRegistro(pos);

    bool continuar = true;
    while(continuar){
        limpiarConsola();
        rlutil::setColor(PaletaCafe::CREMA);
        cout << "EDITANDO A: " << e.getNombre() << " " << e.getApellido() << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(40);
        rlutil::setColor(PaletaCafe::CREMA);
        cout << "1. Modificar Nombre" << endl;
        cout << "2. Modificar Apellido" << endl;
        cout << "3. Modificar Puesto" << endl;
        cout << "4. Modificar Telefono" << endl;
        cout << "5. Modificar Mail" << endl;
        cout << "0. Guardar y Salir" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(40);
        restaurarColor();
        int opc = ingresarEntero("Opcion: ");

        // Variables auxiliares para inputs
        char auxCadena[50];

        switch(opc){
            case 1:
                cargarCadenaObligatoria("Nuevo Nombre: ", "Dato obligatorio", auxCadena, 30);
                e.setNombre(auxCadena); break;
            case 2:
                cargarCadenaObligatoria("Nuevo Apellido: ", "Dato obligatorio", auxCadena, 30);
                e.setApellido(auxCadena); break;
            case 3:
                cout << "Nuevo Puesto: "; cargarCadena(auxCadena, 20);
                e.setPuesto(auxCadena); break;
            case 4:
                cargarCadenaObligatoria("Nuevo Telefono: ", "Dato obligatorio", auxCadena, 20);
                e.setTelefono(auxCadena); break;
            case 5:
                cargarCadenaObligatoria("Nuevo Mail: ", "Dato obligatorio", auxCadena, 40);
                e.setMail(auxCadena); break;
            case 0:
                continuar = false; break;
            default:
                imprimirMensajeError("Opcion invalida."); pausarConsola(); break;
        }
    }

    if (arc.modificarRegistro(e, pos)) cout << endl << ">>> Cambios guardados." << endl;
    else cout << endl << ">>> Error al guardar cambios." << endl;
}

// ==========================================
// FUNCIONES PRIVADAS (HELPERS)
// ==========================================

// Busca un empleado por ID y verifica su estado (si está eliminado o no)
// Retorna la posición en el archivo o -1 si no se encuentra o no cumple el estado
int buscarEmpleadoID(ArchivoEmpleado& arc, bool buscarEliminados) {
    if (!arc.hayEmpleadosConEstadoEliminado(buscarEliminados)) {
        cout << "No hay empleados " << (buscarEliminados ? "eliminados" : "activos") << " disponibles." << endl;
        return -1;
    }

    listarEmpleados(buscarEliminados);
    cout << endl;

    int id = ingresarEntero("Ingrese ID del Empleado: ");
    int pos = arc.buscarRegistro(id);

    if (pos == -1) {
        cout << ">>> ERROR: ID no encontrado." << endl;
        return -1;
    }

    Empleado e = arc.leerRegistro(pos);

    if (e.getEliminado() != buscarEliminados) {
        cout << ">>> ERROR: El empleado seleccionado "
             << (e.getEliminado() ? "esta eliminado" : "esta activo")
             << " y usted busca lo opuesto." << endl;
        return -1;
    }

    return pos;
}

void mostrarEncabezadoEmpleados() {
    lineaDoble(118);
    // Usamos las columnas corregidas en Tablas.cpp
    imprimirFilaEmpleado("ID", "NOMBRE", "APELLIDO", "TELEFONO", "MAIL", "PUESTO");
    lineaSimple(118);
}

void mostrarFilaEmpleado(Empleado e) {
    char sId[10];
    // CORRECCION AQUI: Usamos e.getId() en lugar de e.getIdEmpleado()
    sprintf(sId, "%d", e.getId());

    imprimirFilaEmpleado(sId,
                         e.getNombre(),
                         e.getApellido(),
                         e.getTelefono(),
                         e.getMail(),
                         e.getPuesto());
}

void ordenarEmpleadosPorApellido(Empleado registros[], int cantidad){
    for(int i = 0; i < cantidad - 1; i++){
        for(int j = i + 1; j < cantidad; j++){
            if(strcmp(registros[i].getApellido(), registros[j].getApellido()) > 0){
                Empleado aux = registros[i];
                registros[i] = registros[j];
                registros[j] = aux;
            }
        }
    }
}
