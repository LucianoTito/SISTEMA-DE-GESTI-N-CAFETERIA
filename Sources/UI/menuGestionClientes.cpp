#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "../../Headers/UI/menuGestionClientes.h"
#include "../../Headers/Entities/Cliente.h"
#include "../../Headers/Entities/Pedido.h"
#include "../../Headers/Persistence/ArchivoCliente.h"
#include "../../Headers/Persistence/ArchivoPedido.h"
#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;

// Declaraciones auxiliares.
void listarClientesConMasPedidos();
void listarClientesPorMontoGastado();

void menuClientes(){


    while(true){

        system ("cls");

         cout << "---------- GESTION DE CLIENTES ----------"<<endl;
         cout << "========================================="<<endl;
         cout << "1. AGREGAR CLIENTE"<<endl;
         cout << "2. LISTADOS DE CLIENTES"<<endl;
         cout << "3. MODIFICAR CLIENTE"<<endl;
         cout << "4. ELIMINAR CLIENTE"<<endl;
         cout << "5. DAR DE ALTA A UN CLIENTE"<<endl;
         cout << "------------------------------------------"<<endl;
         cout << "0. VOLVER AL MENU PRINCIPAL"<<endl;
         cout << "=========================================="<<endl;
         cout <<endl;

         int opcion = ingresarEntero("SELECCIONE UNA OPCION: ");

         system("cls");

         // Se controla manualmente la pausa para no mostrarla al volver al menú anterior.
         bool mostrarPausa = true;

         switch(opcion){
     case 1:
        agregarCliente();
        break;
     case 2:
         // El submenú de listados maneja sus propias pausas; si el usuario elige volver,
        // se evita pausar nuevamente al regresar a este menú.
        mostrarPausa = listarClientes();
        break;
     case 3:
        modificarCliente();
        break;
     case 4:
        bajaCliente();
        break;
     case 5:
        altaCliente();
        break;
     case 0:
         mostrarPausa = false;
        return;
     default:
        cout<< "Opcion incorrecta. Vuelva a intentarlo."<<endl;
        break;

         }

        if(mostrarPausa){
            system("pause");
        }

    }

}

void agregarCliente(){

ArchivoCliente arcCliente("Clientes.dat");

Cliente regCliente;

int nuevoID = arcCliente.contarRegistros() + 1 ;

cout << "---------- AGREGAR UN NUEVO CLIENTE ----------"<<endl;

regCliente.Cargar(nuevoID);

bool grabadoExitosamente = arcCliente.grabarRegistro(regCliente);

if (grabadoExitosamente){

    cout << "Cliente agregado exitosamente."<<endl;
} else{
cout << "ERROR: No se pudo agregar el cliente."<<endl;
}


}

bool listarClientes(){

  ArchivoCliente arcCliente("Clientes.dat");

// cout << "======= LISTADO DE CLIENTES ======"<<endl;
  bool hayActivos = arcCliente.hayClientesConEstadoEliminado(false);
  bool hayEliminados = arcCliente.hayClientesConEstadoEliminado(true);


  if(!hayActivos && !hayEliminados){

        cout<< "No hay Clientes activos o inactivos registrados para listar."<<endl;
        cout<< endl;
        // Hay información importante para leer, por lo que se mantiene la pausa aquí.
        system("pause");
        // Se devuelve false para evitar una pausa adicional al regresar al menú anterior.
        return false;
    }

while(true){

    system("cls");

    cout << "================= LISTADOS DE CLIENTES =================="<<endl;
    cout << "1. CLIENTES ACTIVOS"<<endl;
    cout << "2. CLIENTES DADOS DE BAJA"<<endl;
    cout << "3. LISTADO ORDENADO POR APELLIDO"<<endl;
    cout << "4. LISTADO DE CLIENTES CON MAS PEDIDOS (De mayor a menor)"<<endl;
    cout << "5. CLIENTES QUE SUPERAN UN MONTO GASTADO"<<endl;
    cout << "---------------------------------------------------------"<<endl;
    cout << "0. VOLVER AL MENU ANTERIOR"<<endl;
    cout << "========================================================="<<endl;
    cout << endl;

    int opcionListado = ingresarEntero("Seleccione una opcion: ");

    system("cls");

    // La pausa solo se muestra cuando se ejecuta una acción distinta a volver.
    bool mostrarPausa = true;

    switch(opcionListado){
    case 1:

        arcCliente.listar();
        break;
    case 2:
        arcCliente.listarEliminados();
        break;
    case 3:
        arcCliente.listarOrdenadosPorApellido();
        break;
    case 4:
        listarClientesConMasPedidos();
        break;
    case 5:
        listarClientesPorMontoGastado();
        break;
    case 0:
        mostrarPausa = false;
        return false;
    default:
        cout<< "Opcion incorrecta. Vuelva a intentarlo."<<endl;
        break;
    }

    cout<<endl;
   if(mostrarPausa){
        system("pause");
    }
}

// El flujo del menú es un bucle infinito que retorna al seleccionar la opción 0.
// Se devuelve false para indicar que el menú superior no debe agregar una pausa extra.
    return false;

}

void listarClientesConMasPedidos(){

    ArchivoCliente arcCliente("Clientes.dat");
    ArchivoPedido arcPedido("Pedidos.dat");

    cout << "======= CLIENTES CON MAS PEDIDOS ======="<<endl;

    // Primero verifico si existen clientes activos.
    if(!arcCliente.hayClientesConEstadoEliminado(false)){
        cout << "No hay clientes activos para analizar."<<endl;
        return;
    }

    int totalClientes = arcCliente.contarRegistros();

    // Valido que efectivamente existan registros cargados.
    if(totalClientes == 0){
        cout << "El archivo de clientes esta vacio."<<endl;
        return;
    }

    // Reservo memoria para cargar los clientes activos en RAM.
    Cliente *clientesActivos = new Cliente[totalClientes];
    int cantidadActivos = 0;

    // Recorro el archivo copiando solo los clientes activos.
    for(int i=0; i<totalClientes; i++){

        // Leo cada registro del archivo
        Cliente reg = arcCliente.leerRegistro(i);

        // Si el ID es válido y no está eliminado, lo tomo como cliente activo
        if(reg.getId() != -1 && reg.getEliminado()==false){
            clientesActivos[cantidadActivos] = reg;
            cantidadActivos++;   // Incremento el contador de clientes activos
        }
    }

    // Si después de filtrar todos estaban dados de baja, no tengo nada para analizar
    if(cantidadActivos == 0){
        cout << "Todos los clientes estan dados de baja."<<endl;
        delete[] clientesActivos;
        return;
    }

    // Creo un arreglo para contar la cantidad de pedidos de cada cliente activo.
    int *contadorPedidos = new int[cantidadActivos];

    // Inicializo todos los contadores en cero, porque recién voy a comenzar a acumular.
    for(int i=0; i<cantidadActivos; i++){
        contadorPedidos[i] = 0;
    }

    int totalPedidos = arcPedido.contarRegistros();

    // Sin pedidos no puedo hacer el ranking.
    if(totalPedidos == 0){
        cout << "No hay pedidos registrados para analizar."<<endl;
        delete[] clientesActivos;
        delete[] contadorPedidos;
        return;
    }

    // Recorro todos los pedidos activos del sistema
    for(int i=0; i<totalPedidos; i++){
        Pedido pedido = arcPedido.leerRegistro(i);

        // Solo considero los pedidos válidos y activos
        if(pedido.getIdPedido() != -1 && pedido.getEliminado()==false){

            int idClientePedido = pedido.getIdCliente();

            // Busco a cuál cliente activo pertenece este pedido
            for(int j=0; j<cantidadActivos; j++){

                // Cuando encuentro el cliente adecuado, incremento su contador
                if(clientesActivos[j].getId() == idClientePedido){
                    contadorPedidos[j]++;
                    break; // Corto porque ya encontré al cliente dueño del pedido
                }
            }
        }
    }

    int maxPedidos = 0;

    // Identifico cuál es el mayor número de pedidos entre todos los clientes activos
    for(int i=0; i<cantidadActivos; i++){
        if(contadorPedidos[i] > maxPedidos){
            maxPedidos = contadorPedidos[i];
        }
    }

    // Si el máximo es cero, significa que no hicieron ningún pedido todavía
    if(maxPedidos == 0){
        cout << "Los clientes activos aun no tienen pedidos cargados."<<endl;
        delete[] clientesActivos;
        delete[] contadorPedidos;
        return;
    }

     // Ordeno los clientes activos por cantidad de pedidos en forma descendente
    for(int i=0; i<cantidadActivos - 1; i++){
        for(int j=i + 1; j<cantidadActivos; j++){
            if(contadorPedidos[j] > contadorPedidos[i]){
                int auxPedidos = contadorPedidos[i];
                contadorPedidos[i] = contadorPedidos[j];
                contadorPedidos[j] = auxPedidos;

                Cliente auxCliente = clientesActivos[i];
                clientesActivos[i] = clientesActivos[j];
                clientesActivos[j] = auxCliente;
            }
        }
    }


    // Muestro todos los clientes ordenados por pedidos en formato tabular.
    cout << endl;

    cout << "Clientes ordenados por cantidad de pedidos:"<<endl;
    cout << left
         << setw(6) << "ID"
         << setw(15) << "Nombre"
         << setw(15) << "Apellido"
         << setw(12) << "Pedidos" << endl;
    cout << string(48, '-') << endl;


    for(int i=0; i<cantidadActivos; i++){

            if(contadorPedidos[i] == 0){
            break;
        }

        cout << left
             << setw(6) << clientesActivos[i].getId()
             << setw(15) << clientesActivos[i].getNombre()
             << setw(15) << clientesActivos[i].getApellido()
             << setw(12) << contadorPedidos[i]
             << endl;


    }

    cout << string(48, '-') << endl;

    //libero memoria
    delete[] clientesActivos;
    delete[] contadorPedidos;
}

void listarClientesPorMontoGastado(){

    ArchivoCliente arcCliente("Clientes.dat");
    ArchivoPedido arcPedido("Pedidos.dat");

    cout << "======= CLIENTES QUE SUPERAN UN MONTO ======="<<endl;

    // Verifico que haya clientes activos para poder evaluar montos.
    if(!arcCliente.hayClientesConEstadoEliminado(false)){
        cout << "No hay clientes activos para analizar."<<endl;
        return;
    }

    // Pido al usuario el monto mínimo que quiere evaluar.
    float montoMinimo = ingresarFloat("Ingrese el monto minimo acumulado que desea consultar: ");

    int totalClientes = arcCliente.contarRegistros();

    // Si el archivo está vacío, no tengo nada para trabajar.
    if(totalClientes == 0){
        cout << "El archivo de clientes esta vacio."<<endl;
        return;
    }

    Cliente *clientesActivos = new Cliente[totalClientes];
    int cantidadActivos = 0;

    // Sólo copio clientes activos del archivo al vector en memoria
    for(int i=0; i<totalClientes; i++){
        Cliente reg = arcCliente.leerRegistro(i);

        if(reg.getId() != -1 && reg.getEliminado()==false){
            clientesActivos[cantidadActivos] = reg;
            cantidadActivos++;
        }
    }

    // Si todos estaban eliminados, no hay nada para analizar
    if(cantidadActivos == 0){
        cout << "Todos los clientes estan dados de baja."<<endl;
        delete[] clientesActivos;
        return;
    }

    // Vector que llevará el total gastado por cada cliente activo
    float *totalGastado = new float[cantidadActivos];

    // Inicializo todos los acumuladores en cero
    for(int i=0; i<cantidadActivos; i++){
        totalGastado[i] = 0.0f;
    }

    int totalPedidos = arcPedido.contarRegistros();

    // Sin pedidos no puedo calcular montos gastados
    if(totalPedidos == 0){
        cout << "No hay pedidos registrados para calcular montos."<<endl;
        delete[] clientesActivos;
        delete[] totalGastado;
        return;
    }

    // Recorro todos los pedidos válidos y sumo en cada cliente su gasto total
    for(int i=0; i<totalPedidos; i++){
        Pedido pedido = arcPedido.leerRegistro(i);

        // Solo acumulo pedidos válidos y activos
        if(pedido.getIdPedido() != -1 && pedido.getEliminado()==false){

            int idClientePedido = pedido.getIdCliente();

            // Busco en la lista de clientes activos cuál coincide
            for(int j=0; j<cantidadActivos; j++){

                // Cuando lo encuentro, sumo el total del pedido al cliente
                if(clientesActivos[j].getId() == idClientePedido){
                    totalGastado[j] += pedido.getTotal();
                    break; // Corto el bucle porque ya encontré el cliente correcto
                }
            }
        }
    }

    bool hayCoincidencias = false;

    cout << endl;
    cout << "Clientes con gastos iguales o superiores a $" << montoMinimo << ":"<<endl;
    cout << left
         << setw(6) << "ID"
         << setw(15) << "Nombre"
         << setw(15) << "Apellido"
         << setw(18) << "Total gastado" << endl;
    cout << string(54, '-') << endl;


    // Muestro todos los clientes cuyo monto acumulado supera el mínimo ingresado
    for(int i=0; i<cantidadActivos; i++){
        if(totalGastado[i] >= montoMinimo){

            cout << left
                 << setw(6) << clientesActivos[i].getId()
                 << setw(15) << clientesActivos[i].getNombre()
                 << setw(15) << clientesActivos[i].getApellido()
                 << "$ " << fixed << setprecision(2) << totalGastado[i] << endl;

            hayCoincidencias = true;
        }
    }

    // Si no encontré ninguno, informo
    if(!hayCoincidencias){
        cout << "Ningun cliente activo supera el monto indicado."<<endl;
    }

    cout << string(54, '-') << endl;

    // Libero la memoria
    delete[] clientesActivos;
    delete[] totalGastado;
}

void modificarCliente(){

ArchivoCliente arcCliente("Clientes.dat");

if(!arcCliente.hayClientesConEstadoEliminado(false)){
    cout << "No hay clientes activos para modificar."<<endl;
    return;
}


cout << "--------- MODIFICAR CLIENTE ---------"<<endl;

arcCliente.listar();

cout <<endl;
int idModificar = ingresarEntero("Ingrese el ID del cliente que quiere modificar: ");

int posicionId = arcCliente.buscarRegistro(idModificar);

if (posicionId == -1){

    cout << "ERROR. No se encontró un cliente con el  ID: "<<idModificar<<endl;
    return;
}

//Si se ecnontró , leer el registro actual en esa posición
Cliente reg = arcCliente.leerRegistro(posicionId);

if(reg.getEliminado()==true){
    cout << "El cliente seleccionado no se encuentra activo."<<endl;
    return;
}

cout << "Cliente encontrado. Datos actuales:"<<endl;
reg.Mostrar();

cout<< endl;

// Menú para modificar un único campo sin volver a cargar todo el cliente
cout << "¿Qué desea modificar?"<<endl;
cout << "1) Nombre"<<endl;
cout << "2) Apellido"<<endl;
cout << "3) Telefono"<<endl;
cout << "4) Mail"<<endl;
cout << "0) Cancelar"<<endl;

int opcionCampo;

// Validación de la opción elegida
do {
    opcionCampo = ingresarEntero("Ingrese una opcion: ");
    if(opcionCampo < 0 || opcionCampo > 4){
        cout << "Opcion incorrecta. Intente nuevamente."<<endl;
    }
} while(opcionCampo < 0 || opcionCampo > 4);

// Se pide solo el dato seleccionado. Cada caso reutiliza las validaciones existentes.
switch(opcionCampo){

case 1:{
    char nuevoNombre[30];
    cargarCadenaObligatoria("Ingrese el nuevo nombre: ",
                            "El nombre no puede quedar vacio.",
                            nuevoNombre,
                            30);
    reg.setNombre(nuevoNombre);
    break;
}

case 2:{
    char nuevoApellido[30];
    cargarCadenaObligatoria("Ingrese el nuevo apellido: ",
                            "El apellido no puede quedar vacio.",
                            nuevoApellido,
                            30);
    reg.setApellido(nuevoApellido);
    break;
}

case 3:{
    char nuevoTelefono [20];
    cargarCadenaObligatoria("Ingrese el nuevo numero de telefono: ",
                            "El telefono no puede quedar vacio.",
                            nuevoTelefono,
                            20);
    reg.setTelefono(nuevoTelefono);
    break;
}

case 4:{
    char nuevoMail[40];
    cargarCadenaObligatoria("Ingrese el nuevo mail: ",
                            "El mail no puede quedar vacio.",
                            nuevoMail,
                            40);
    reg.setMail(nuevoMail);
    break;
}

case 0:
    cout << "Modificacion cancelada por el usuario."<<endl;
    return;
}


bool grabadoExitosamente = arcCliente.modificarRegistro(reg, posicionId);

if (grabadoExitosamente){
    cout << "Cliente modificado exitosamente."<<endl;
} else {
cout<< "ERROR. No se pudo modificar el cliente. Verifique los datos e intente nuevamente."<<endl;
}

}

void bajaCliente(){

    ArchivoCliente arcCliente("Clientes.dat");

    if(!arcCliente.hayClientesConEstadoEliminado(false)){

        cout << "No hay clientes activos para eliminar."<<endl;
        return;
    }


    cout << "---------- ELIMINAR CLIENTE ----------"<<endl;

    arcCliente.listar();
    cout <<endl;
    int idEliminar = ingresarEntero("Ingrese el ID del cliente que desea eliminar: ");

    int posicionId = arcCliente.buscarRegistro(idEliminar);

    if (posicionId == -1){

        cout << "ERROR. No se encontro un cliente con el ID: "<<idEliminar<<endl;
        return;
    }
//En caso de que se haya encontrado, leer el registro actual
Cliente reg = arcCliente.leerRegistro(posicionId);

cout<< "Cliente encontrado: "<<endl;
reg.Mostrar();
cout<<endl;

//Si ya estaba eliminado
if (reg.getEliminado()==true){
    cout<< "Este cliente ya se encuentra eliminado."<<endl;
    return;
}

char confirmacion;
cout<< "Esta seguro de que desea eliminar a este cliente? (S/N): ";
cin>>confirmacion;

if (confirmacion == 'S' || confirmacion == 's'){

   //Actualizar el objeto en memoria
    reg.setEliminado(true);

    //grabar el registro de vuelta en el archivo
    bool grabadoExitosamente = arcCliente.modificarRegistro(reg, posicionId);

    if(grabadoExitosamente){
        cout<< "Cliente dado de baja exitosamente."<<endl;
    }else {
        cout << "ERROR. No se pudo eliminar el cliente con el ID: "<<idEliminar<<endl;
    }
} else {
    cout << "OPERACION CANCELADA"<<endl;
}

}

void altaCliente(){

ArchivoCliente arcCliente("Clientes.dat");

if (!arcCliente.hayClientesConEstadoEliminado(true)){

    cout<< "No hay clientes dados de baja para dar de alta"<<endl;
    return;
}

cout<< "------- DAR DE ALTA CLIENTE -------"<<endl;

arcCliente.listarEliminados();
cout<<endl;
int idRecuperar = ingresarEntero("Ingrese el ID del cliente que desea activar nuevamente: ");

int posicionId = arcCliente.buscarRegistro(idRecuperar);

if(posicionId == -1){

    cout << "ERROR. No se encontro un cliente con el ID: "<<idRecuperar<<endl;
    return;
}

Cliente reg = arcCliente.leerRegistro(posicionId);

if(reg.getEliminado() == false){

    cout<< "El cliente seleccionado ya se encuentra activo."<<endl;
    return;
}

reg.setEliminado(false);

bool grabadoExitosamente = arcCliente.modificarRegistro(reg, posicionId);

if (grabadoExitosamente){
        cout << "Cliente dado de alta exitosamente."<<endl;
} else {
        cout << "ERROR. No se pudo dar de alta al cliente."<<endl;
}


}
