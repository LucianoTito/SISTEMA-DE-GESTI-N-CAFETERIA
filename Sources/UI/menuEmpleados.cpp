#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>

#include "../../Headers/UI/menuEmpleados.h"
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/Persistence/ArchivoEmpleado.h"
#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;


void ordenarEmpleadosPorApellido(Empleado registros[], int cantidad);

void menuEmpleados(){

// Archivo de empleados para operaciones de listado dentro del menú principal.
    ArchivoEmpleado arcEmpleado("Empleados.dat");

    while(true){
        system("cls");
        cout << "---------- GESTION DE EMPLEADOS ----------"<<endl;
        cout << "=========================================="<<endl;
        cout << "1. AGREGAR EMPLEADO"<<endl;
        cout << "2. EMPLEADOS ACTIVOS"<<endl;
        cout << "3. EMPLEADOS DADOS DE BAJA"<<endl;
        cout << "4. MODIFICAR EMPLEADO"<<endl;
        cout << "5. ELIMINAR EMPLEADO"<<endl;
        cout << "6. DAR DE ALTA EMPLEADO"<<endl;
        cout << "7. LISTAR EMPLEADOS ORDENADOS POR APELLIDO"<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "0. VOLVER AL MENU PRINCIPAL" <<endl;
        cout << "=========================================="<<endl;
        cout <<endl;

        int opcion = ingresarEntero("SELECCIONE UNA OPCION: ");

        system("cls");

        // La pausa se controla manualmente para evitarla al regresar al menú anterior.
        bool mostrarPausa = true;

        switch (opcion){
    case 1:
        agregarEmpleado();
        break;
    case 2:
        arcEmpleado.listar();
        break;
    case 3:
        arcEmpleado.listarEliminados();
        break;
    case 4:
        modificarEmpleado();
        break;
    case 5:
        bajaEmpleado();
        break;
    case 6:
        listarEmpleadosOrdenadosPorApellido();
        break;
    case 7:
        listarEmpleadosOrdenadosPorApellido();
        break;
    case 0:
        mostrarPausa = false;
        return;
    default:
        cout << "Opcion incorrecta. Vuelva a intentarlo."<<endl;
        break;

        }

        if(mostrarPausa){
            system("pause");
        }

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



void listarEmpleadosOrdenadosPorApellido(){

ArchivoEmpleado arcEmpleado("Empleados.dat");

int totalRegistros = arcEmpleado.contarRegistros();

if(totalRegistros == 0){
    cout << "No hay empleados registrados para ordenar."<<endl;
    return;
}

Empleado *registros = new Empleado[totalRegistros];

int cantidadLeida = arcEmpleado.leerRegistros(registros, totalRegistros);

if(cantidadLeida == 0){
    cout << "No fue posible leer los empleados almacenados."<<endl;
    delete [] registros;
    return;
}

int cantidadActivos = 0;

for(int i = 0; i < cantidadLeida; i++){
    if(registros[i].getEliminado() == false){
        registros[cantidadActivos] = registros[i];
        cantidadActivos++;
    }
}

if(cantidadActivos == 0){
    cout << "No hay empleados activos para mostrar."<<endl;
    delete [] registros;
    return;
}

ordenarEmpleadosPorApellido(registros, cantidadActivos);

cout << "----- LISTADO ORDENADO POR APELLIDO -----"<<endl;
// Se muestra en tabla sin columna de estado porque todos son activos.
cout << left
     << setw(6) << "ID"
     << setw(15) << "Nombre"
     << setw(15) << "Apellido"
     << setw(18) << "Telefono"
     << setw(25) << "Mail"
     << setw(15) << "Puesto" << endl;
cout << string(94, '-') << endl;

for(int i = 0; i < cantidadActivos; i++){
    registros[i].MostrarFila();
}

cout << string(94, '-') << endl;

delete [] registros;


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
int idModificar = ingresarEntero("Ingrese el ID del empleado que desea modificar: ");

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

// Menú para modificar solo un campo y evitar repetir la carga completa
cout << "¿Qué desea modificar?"<<endl;
cout << "1) Nombre"<<endl;
cout << "2) Apellido"<<endl;
cout << "3) Puesto"<<endl;
cout << "4) Telefono"<<endl;
cout << "5) Mail"<<endl;
cout << "0) Cancelar"<<endl;

int opcionCampo;

//Validación de opción ingresada
do {
    opcionCampo = ingresarEntero("Ingrese una opcion: ");
    if(opcionCampo < 0 || opcionCampo > 5){
        cout << "Opcion incorrecta. Intente nuevamente."<<endl;
    }

}while(opcionCampo < 0 || opcionCampo > 5);

switch(opcionCampo){

case 1: {
        char nuevoNombre[30];
        cargarCadenaObligatoria("Ingrese el nuevo nombre: ",
                                "El nombre no puede quedar vacio.",
                                nuevoNombre,
                                30);
        reg.setNombre(nuevoNombre);
        break;

}

case 2: {
        char nuevoApellido[30];
        cargarCadenaObligatoria("Ingrese el nuevo apellido: ",
                                "El apellido no puede quedar vacio.",
                                nuevoApellido,
                                30);
        reg.setApellido(nuevoApellido);
        break;
}

case 3: {
        char nuevoPuesto[20];
        cout << "Ingrese el nuevo puesto: ";
        cargarCadena(nuevoPuesto, 20);
        reg.setPuesto(nuevoPuesto);
        break;
}

case 4: {
        char nuevoTelefono[20];
        cargarCadenaObligatoria("Ingrese el nuevo telefono: ",
                                "El telefono no puede quedar vacio.",
                                nuevoTelefono,
                                20);
        reg.setTelefono(nuevoTelefono);
        break;
        }

case 5: {
char nuevoMail[40];
cargarCadenaObligatoria("Ingrese el nuevo mail: ",
                        "El mail no puede quedar vacio.",
                        nuevoMail,
                        40);
        reg.setMail(nuevoMail);
        break;
}


case 0:
    cout << "Modificacion cancelada por el usuario." <<endl;
    return;
}
//Grabar el registro modificado de vuelta en el archivo con el dato actualizado
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
cout << "Esta seguro que desea dar de baja a este empleado (S/N)? : ";
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
