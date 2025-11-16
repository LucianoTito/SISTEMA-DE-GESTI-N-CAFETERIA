#include <iostream>
#include <cstdlib>

#include "../../Headers/Persistence/ArchivoEmpleado.h"
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/Persistence/ArchivoEmpleado.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include"../../Headers/UI/menuEmpleados.h"

using namespace std;

void menuEmpleados(){

    while(true){
        system("cls");
        cout << "---------- GESTION DE EMPLEADOS ----------"<<endl;
        cout << "=========================================="<<endl;
        cout << "1. AGREGAR EMPLEADO"<<endl;
        cout << "2. LISTAR EMPLEADOS"<<endl;
        cout << "3. MODIFICAR EMPLEADO"<<endl;
        cout << "4. ELIMINAR EMPLEADO"<<endl;
        cout << "5. DAR DE ALTA EMPLEADO"<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "0. VOLVER AL MENU PRINCIPAL" <<endl;
        cout << "=========================================="<<endl;
        cout <<endl;

        int opcion = ingresarEntero("SELECCIONE UNA OPCION: ");

        system("cls");

        switch (opcion){
    case 1:
        agregarEmpleado();
        break;
    case 2:
        listarEmpleados();
        break;
    case 3:
        modificarEmpleado();
        break;
    case 4:
        bajaEmpleado();
        break;
    case 5:
        altaEmpleado();
        break;
    case 0:
        return;
    default:
        cout << "Opcion incorrecta. Vuelva a intentarlo."<<endl;
        break;

        }
        system("pause");
    }


}

void agregarEmpleado(){

ArchivoEmpleado arcEmpleado("Empleados.dat");

Empleado regEmpleado;

//Calculo de ID autoincremental
int nuevoID = arcEmpleado.contarRegistros()+1;
cout << "---------- AGREGAR NUEVO EMPLEADO ----------"<<endl;

regEmpleado.Cargar(nuevoID);

bool grabarExitosamente = arcEmpleado.grabarRegistro(regEmpleado);

if (grabarExitosamente){
    cout << "Empleado agregado existosamente."<<endl;

}else {
 cout << "ERROR. No se pudo agregar al empleado con ID: "<<nuevoID<<endl;
}

}

void listarEmpleados(){

    ArchivoEmpleado arcEmpleado("Empleados.dat");

    cout << "===== LISTADO DE EMPLEADOS ====="<<endl;

bool hayActivos = arcEmpleado.hayEmpleadosConEstadoEliminado(false);
bool hayEliminados = arcEmpleado.hayEmpleadosConEstadoEliminado(true);


if(!hayActivos && !hayEliminados){
    cout<< endl;
    cout<< "No hay productos activos o inactivos registrados para listar."<<endl;
    cout<< endl;
    return;
}

    arcEmpleado.listar();
    arcEmpleado.listarEliminados();

}

void modificarEmpleado(){

ArchivoEmpleado arcEmpleado("Empleados.dat");

if(!arcEmpleado.hayEmpleadosConEstadoEliminado(false)){

    cout << "No hay empleados activos para modificar."<<endl;
    return;
}


cout << "------- MODIFICAR EMPLEADO -------"<<endl;
arcEmpleado.listar();

cout <<endl;
int idModificar = ingresarEntero("Ingrese el ID del empleado que desea modificar");

int posicionID = arcEmpleado.buscarRegistro(idModificar);

if(posicionID == -1){
    cout << "ERROR. No se encontro un empleado con el ID: "<<idModificar<<endl;
    return;
}

Empleado reg = arcEmpleado.leerRegistro(posicionID);

if(reg.getEliminado()== true){

    cout << "El empleado seleccionado no se encuentra activo. No se puede modificar."<<endl;
    return;
}

cout << "Empleado encontrado. Datos actuales: "<<endl;
reg.Mostrar();
cout<<endl;

//Pedir los nuevos datos (solo se puede modificar el puesto)
char nuevoPuesto[20];
cout << "Ingrese el nuevo puesto: ";

//Actualizar el objeto reg en memoria
reg.setPuesto(nuevoPuesto);

//Grabar el registro modificado de vuelta en el archivo
bool grabadoExitosamente = arcEmpleado.modificarRegistro(reg, posicionID);

if(grabadoExitosamente){

    cout << "Empleado modificado exitosamente."<<endl;
} else {
    cout<< "ERROR. No se pudo modificar el empleado con ID: "<<idModificar<<endl;
}


}

void bajaEmpleado(){

ArchivoEmpleado arcEmpleado("Empleados.dat");

if(!arcEmpleado.hayEmpleadosConEstadoEliminado(false)){

    cout<< "No hay empleados activos para eliminar."<<endl;
    return;
}


cout << "------- ELIMINAR EMPLEADO -------"<<endl;
arcEmpleado.listar();

cout <<endl;
int idEliminar = ingresarEntero("Ingrese el ID del empleado que quiere eliminar: ");

int posicionId= arcEmpleado.buscarRegistro(idEliminar);

if (posicionId == -1){

    cout<<endl;
    cout << "ERROR. No se encontro un empelado con el ID: "<<idEliminar<<endl;
    return;
}
//Si se pudo econtrar
Empleado reg = arcEmpleado.leerRegistro(posicionId);

cout << "Empleado encontrado: "<<endl;
reg.Mostrar();
cout<<endl;


//Verifiación por si ya estaba eliminado
if (reg.getEliminado()==true){
    cout << "Este empleado ya se encuentra eliminado."<<endl;
    return;
}

char confirmacion;
cout << "Esta seguro que desea dar de baja a este empleado? (S/N)";
cin>> confirmacion;

if (confirmacion == 'S'|| confirmacion == 's'){

    reg.setEliminado(true);

    bool grabadoExitosamente = arcEmpleado.modificarRegistro(reg, posicionId);

    if(grabadoExitosamente){
        cout << "Empleado dado de baja correctamente."<<endl;
    }else {
        cout << "ERROR. No se pudo dar de baja al empleado con ID: "<< idEliminar<<endl;
        cout<<endl;
    }
}else {
    cout << "Operacion cancelada."<<endl;
}


}

void altaEmpleado(){

ArchivoEmpleado arcEmpleado("Empleados.dat");

if (!arcEmpleado.hayEmpleadosConEstadoEliminado(true)){

    cout<<endl;
    cout<< "No hay empleados dados de baja para dar de alta."<<endl;
    cout<<endl;
    return;
}


cout << "---- DAR DE ALTA EMPLEADO ----"<<endl;
arcEmpleado.listarEliminados();

cout<<endl;
int idRecuperar = ingresarEntero("Ingrese el ID del empleado que desea activar nuevamente");

int posicionId = arcEmpleado.buscarRegistro(idRecuperar);

if(posicionId == -1){

    cout << "ERROR. No se encontro un empleado con el ID: "<<idRecuperar<<endl;
    cout<<endl;
    return;
}

Empleado reg = arcEmpleado.leerRegistro(posicionId);

if(reg.getEliminado()== false){

    cout<< "El empleado seleccionado ya se encuentra activo"<<endl;
    cout<<endl;
    return;
}

reg.setEliminado(false);

bool grabadoExitosamente = arcEmpleado.modificarRegistro(reg, posicionId);

if (grabadoExitosamente){
    cout << "Empleado dado de alta exitosamente."<<endl;

}else {
    cout << "ERROR. No se pudo dar de alta al empleado."<<endl;
    cout<<endl;
}



}
