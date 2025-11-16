#include <iostream>
#include <cstdlib>

#include "../../Headers/UI/menuGestionClientes.h"
#include "../../Headers/Entities/Cliente.h"
#include "../../Headers/Persistence/ArchivoCliente.h"
#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;

void menuClientes(){


    while(true){

        system ("cls");

         cout << "---------- GESTION DE CLIENTES ----------"<<endl;
         cout << "========================================="<<endl;
         cout << "1. AGREGAR CLIENTE"<<endl;
         cout << "2. LISTAR CLIENTES"<<endl;
         cout << "3. MODIFICAR CLIENTE"<<endl;
         cout << "4. ELIMINAR CLIENTE"<<endl;
         cout << "5. DAR DE ALTA A UN CLIENTE"<<endl;
         cout << "------------------------------------------"<<endl;
         cout << "0. VOLVER AL MENU PRINCIPAL"<<endl;
         cout << "=========================================="<<endl;
         cout <<endl;

         int opcion = ingresarEntero("SELECCIONE UNA OPCION: ");

         system("cls");

         switch(opcion){
     case 1:
        agregarCliente();
        break;
     case 2:
        listarClientes();
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
        return;
     default:
        cout<< "Opcion incorrecta. Vuelva a intentarlo."<<endl;
        break;

         }
system("pause");

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

void listarClientes(){

ArchivoCliente arcCliente("Clientes.dat");

// cout << "======= LISTADO DE CLIENTES ======"<<endl;
bool hayActivos = arcCliente.hayClientesConEstadoEliminado(false);
bool hayEliminados = arcCliente.hayClientesConEstadoEliminado(true);


if(!hayActivos && !hayEliminados){

    cout<< "No hay Clientes activos o inactivos registrados para listar."<<endl;
    cout<< endl;
    return;
}

while(true){

    system("cls");

    cout << "======= LISTADOS DE CLIENTES ======"<<endl;
    cout << "1. LISTADO GENERAL"<<endl;
    cout << "2. LISTADO ORDENADO POR APELLIDO"<<endl;
    cout << "3. LISTADO ORDENADO POR PUNTOS DE FIDELIDAD"<<endl;
    cout << "-----------------------------------"<<endl;
    cout << "0. VOLVER AL MENU ANTERIOR"<<endl;
    cout << "==================================="<<endl;
    cout << endl;

    int opcionListado = ingresarEntero("Seleccione una opcion: ");

    system("cls");

    switch(opcionListado){
    case 1:
        cout << "======= LISTADO DE CLIENTES ======"<<endl;
        arcCliente.listar();
        arcCliente.listarEliminados();
        break;
    case 2:
        arcCliente.listarOrdenadosPorApellido();
        break;
    case 3:
        arcCliente.listarOrdenadosPorPuntosDeFidelidad();
        break;
    case 0:
        return;
    default:
        cout<< "Opcion incorrecta. Vuelva a intentarlo."<<endl;
        break;
    }

    cout<<endl;
    system("pause");
}


}

void modificarCliente(){

ArchivoCliente arcCliente("Clientes.dat");

if(!arcCliente.hayClientesConEstadoEliminado(false)){
    cout << "No hay clientes activos para modificar."<<endl;
    return;
}


cout << "------- MODIFICAR CLIENTE -------"<<endl;

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

//Pedir los nuevos datos
char nuevoTelefono [20];
cout << "Ingrese el nuevo numero de telefono: ";

//Modularizo con cargar cadena
cargarCadena(nuevoTelefono, 20);
reg.setTelefono(nuevoTelefono);

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
cout<< "Esta seguro de que desea eliminar a este cliente? (S/N)";
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
