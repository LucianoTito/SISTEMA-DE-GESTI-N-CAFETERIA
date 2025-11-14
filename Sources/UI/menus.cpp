#include <iostream>
#include <cstdio>

#include "../../Headers/UI/menus.h"

//Includes para los productos
#include "../../Headers/Entities/Producto.h"
#include "../../Headers/Persistence/ArchivoProducto.h"

//Includes para clientes
#include "../../Headers/Entities/Cliente.h"
#include "../../Headers/Persistence/ArchivoCliente.h"

//Includes para Empleados
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/Persistence/ArchivoEmpleado.h"


//Includes para gestion de Pedidos
#include "../../Headers/Entities/Pedido.h"
#include "../../Headers/Persistence/ArchivoPedido.h"
#include "../../Headers/Entities/DetallePedido.h"
#include "../../Headers/Persistence/ArchivoDetallePedido.h"
#include "../../Headers/Entities/Pagos.h"
#include "../../Headers/Persistence/ArchivoPagos.h"


//Include para reportes
#include "../../Headers/UI/reportes.h"

//Include para las configuraciones
#include"../../Headers/UI/configuraciones.h"

//Include de validaciones
#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;

void menuPrincipal() {

    int opcion;

    while (true) {
        system("cls");

        cout << "---- MENU PRINCIPAL DE VENCO CAFE ----" << endl;
        cout << "======================================" << endl;
        cout << "1. GESTION DE PRODUCTOS" << endl;
        cout << "2. GESTION DE CLIENTES" << endl;
        cout << "3. GESTION DE EMPLEADOS" << endl;
        cout << "4. GESTION DE PEDIDOS" << endl;
        cout << "----------------------------------------" << endl;
        cout << "5. REPORTES" << endl;
        cout << "6. CONFIGURACIONES" << endl;
        cout << "----------------------------------------" << endl;
        cout << "0. SALIR" << endl;
        cout << "======================================" << endl;
        cout <<endl ;

        int opcion = ingresarEntero("SELECCIONE UNA OPCION: ");



        system("cls");

        switch (opcion) {
            case 1:

                menuProductos();
                break;
            case 2:

                menuClientes();
                break;
            case 3:

                menuEmpleados();
                break;
            case 4:

                menuPedidos();
                break;
            case 5:

                menuReportes();
                break;
            case 6:

                menuConfiguraciones();
                break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                return;
            default:
                cout << "Opcion incorrecta. Ingrese solo un numero y vuelva a intentarlo." << endl;
                break;
        }
        system("pause");
    }
}

void menuProductos() {


while (true) {
     system("cls");

    cout << "------- GESTION DE PRODUCTOS -------" <<endl;
    cout << "====================================" <<endl;
    cout << "1. AGREGAR PRODUCTO" <<endl;
    cout << "2. LISTAR PRODUCTOS" <<endl;
    cout << "3. MODIFICAR PRODUCTO "<<endl;
    cout << "4. ELIMINAR PRODUCTO "<<endl;
    cout << "5. DAR DE ALTA PRODUCTO" <<endl;
    cout << "------------------------------------" <<endl;
    cout << "0. VOLVER AL MENU PRINCIPAL" <<endl;
    cout << "====================================" <<endl;
    cout <<endl;

    int opcion = ingresarEntero("SELECCIONE UNA OPCION: ");

    system ("cls");


    switch (opcion){
case 1:
    agregarProducto();
    break;

case 2:
    listarProductos();
    break;

case 3:
    modificarProducto();
    break;

case 4:
        bajaProducto();
        break;
case 5:
        altaProducto();
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


void agregarProducto(){

//Crear el obj de la capa de persistencia
ArchivoProducto arcProducto ("Productos.dat");

//Creación del obj
Producto regProducto;

//ID autoincremental
int nuevoID = arcProducto.contarRegistros() + 1;

cout << "-------- AGREGAR NUEVO PRODUCTO --------" <<endl;

//Cargar(nuevoID) pedirá nombre, precio,stock, etc
regProducto.Cargar(nuevoID);

//Grabar el registro en el archivo
bool grabadoExitosamente = arcProducto.grabarRegistro(regProducto);

if(grabadoExitosamente){
    cout << "Producto agregado exitosamente."<<endl;
}else {

cout<< "Error: No se puedo agregar el producto."<<endl;

}



}


void listarProductos(){

ArchivoProducto arcProducto ("Productos.dat");

bool hayActivos = arcProducto.hayProductosConEstadoEliminado(false);
bool hayEliminados = arcProducto.hayProductosConEstadoEliminado(true);


if(!hayActivos && !hayEliminados){

    cout<< "No hay productos activos o inactivos registrados para listar."<<endl;
    cout<< endl;
    return;
}

cout << "----- LISTADO DE PRODUCTOS ACTIVOS -----"<<endl;

arcProducto.listar();
cout<<endl;
cout << "=========================================="<<endl;
cout<<endl;

cout << "----- LISTADO DE PRODUCTOS INACTIVOS -----"<<endl;

arcProducto.listarEliminados();
}

void modificarProducto(){

ArchivoProducto arcProducto ("Productos.dat");

if(!arcProducto.hayProductosConEstadoEliminado(false)){

    cout<< "No hay productos activos para modificar."<<endl;
    return;
}



cout << "----- MODIFICAR PRODUCTO -----" <<endl;
arcProducto.listar();
cout<<endl;
cout <<endl;
int idModificar= ingresarEntero("Ingrese el ID del producto que desaea modificar: ");

//llamando a buscarRegistro() para obtener la POSICIÓN
int posicionID = arcProducto.buscarRegistro(idModificar);

if (posicionID == -1){

    cout << "Error: No se encontro ningun producto con ese ID."<<endl;
    return;
}
//Si se encontró leer el registro
Producto reg = arcProducto.leerRegistro(posicionID);

if(reg.getEliminado()){

    cout << "El producto seleccionado no está activo"<<endl;
    return;
}

cout << "Producto encontrado. Datos actuales: "<<endl;
reg.Mostrar();
cout << endl;


//Pedir los nuevos datos

cout <<endl;
float nuevoPrecio = ingresarFloat("Ingrese el nuevo precio: ");

cout <<endl;
int nuevoStock = ingresarEntero("Ingrese el nuevo stock: ");

//Actualizamos el objeto registro en memoria
reg.setPrecio(nuevoPrecio);
reg.setStock(nuevoStock);

//Grabamos el registro de nuevo en el archivo
bool grabadoExitosamente = arcProducto.modificarRegistro(reg, posicionID);

if(grabadoExitosamente){

    cout << "Producto modificado de manera exitosa."<<endl;

} else {
    cout<< "Error: No se pudo modificar el producto. Verifique los datos e intente nuevamente."<<endl;
}

}

void bajaProducto(){

ArchivoProducto arcProducto ("Productos.dat");

if(!arcProducto.hayProductosConEstadoEliminado(false)){

    cout << "No hay productos activos para eliminar."<<endl;
    return;
}

cout << "-------- ELIMINAR PRODUCTO --------"<<endl;
arcProducto.listar();
cout <<endl;
int idEliminar= ingresarEntero("Ingrese el ID del producto a eliminar: ");

//Buscar el registro
int posicionRegistro = arcProducto.buscarRegistro(idEliminar);

if (posicionRegistro == -1){

    cout << "Error: No se encontro un producto con ese ID."<<endl;
    return;
}

Producto reg = arcProducto.leerRegistro(posicionRegistro);

cout << "Producto encontrado: "<<endl;
reg.Mostrar();
cout <<endl;

if (reg.getEliminado()== true){

    cout << "El producto solicitado ya se contraba eliminado."<<endl;
    return;
}

//Confirmación adicional
char confirmacion;
cout << "Esta seguro que quiere eliminar este producto? (S/N): ";
cin >> confirmacion;

if (confirmacion == 'S' || confirmacion == 's'){

    //Actualizo el objeto reg en MEMORIA
    reg.setEliminado (true);

    //Grabo el registro modificado DE VUELTA en el archivo
    bool grabadoExitosamente = arcProducto.modificarRegistro(reg, posicionRegistro);

    if (grabadoExitosamente){
        cout << "Producto eliminado exitosamente. "<<endl;
    }else {
    cout<< "ERROR. No se pudo eliminar el producto, intente nuevamente."<<endl;
    }
} else {
  cout << "OPERACION CANCELADA."<<endl;
}



}

void altaProducto(){

ArchivoProducto arcProducto("Productos.dat");

if(!arcProducto.hayProductosConEstadoEliminado(true)){

    cout << "No hay productos dado de baja para dar el alta"<<endl;
    return;
}


cout << "---------- DAR DE ALTA PRODUCTO ----------"<<endl;
cout<< "Listado de productos eliminados: "<<endl;
arcProducto.listarEliminados();
cout <<endl;
int idRecuperar = ingresarEntero("Ingrese el ID del producto que desea activar nuevamente: ");

int posicionRegistro = arcProducto.buscarRegistro(idRecuperar);

if(posicionRegistro == -1){

    cout << "Error: No se encontro un producto con ese ID"<<endl;
    return;
}

Producto reg = arcProducto.leerRegistro(posicionRegistro);

if(reg.getEliminado()==false){

    cout<< "El producto seleccionado ya se encuentra activo"<<endl;
    return;
}

reg.setEliminado(false);

bool grabadoExitosamente = arcProducto.modificarRegistro(reg, posicionRegistro);

if (grabadoExitosamente){

    cout << "Producto dado de alta exitosamente."<<endl;
}else {
        cout<< "ERROR. No se pudo dar de alta el producto. Intente nuevamente"<<endl;
}

}







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

cout << "======= LISTADO DE CLIENTES ======"<<endl;

bool hayActivos = arcCliente.hayClientesConEstadoEliminado(false);
bool hayEliminados = arcCliente.hayClientesConEstadoEliminado(true);


if(!hayActivos && !hayEliminados){

    cout<< "No hay Clientes activos o inactivos registrados para listar."<<endl;
    cout<< endl;
    return;
}


arcCliente.listar();
arcCliente.listarEliminados();

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

if(grabadoExitosamente){

    cout << "Cliente dado de alta exitosamente."<<endl;
} else {
        cout << "ERROR. No se pudo dar de alta al cliente."<<endl;
}


}




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




void menuPedidos(){

int opcion;
while (true){
    system ("cls");

    cout << "---------- GESTION DE PEDIDOS ----------" <<endl;
    cout << "========================================" <<endl;
    cout << "1. REALIZAR UN PEDIDO "<< endl;
    cout << "2. VER DETALLE DE UN PEDIDO" <<endl;
    cout << "3. LISTAR TODOS LOS PEDIDOS" <<endl;
    cout << "4. ANULAR UN PEDIDO "<<endl; //baja logica
    cout << "----------------------------------------" <<endl;
    cout << "0. VOLVER AL MENU PRINCIPAL" <<endl;
    cout << "========================================"<< endl;

    opcion = ingresarEntero("SELECCIONE UNA OPCION: ");

    system ("cls");


    switch (opcion){

case 1:
    realizarPedido();
    break;
case 2:
     verDetallePedido();
    break;
case 3:
     listarPedidos();
    break;
case 4:
    anularPedido();
    break;
case 0:
    return;
default:
    cout << "Opcion incorrecta. Vuelva a intentarlo. "<<endl;
    break;


    }
system ("pause");

}

}

void realizarPedido() {

ArchivoCliente arcCliente ("Clientes.dat");
ArchivoEmpleado arcEmpleado ("Empleados.dat");
ArchivoProducto arcProducto ("Productos.dat");
ArchivoPedido arcPedido ("Pedidos.dat");
ArchivoDetallePedido arcDetalle ("DetallesPedidos.dat");
ArchivoPagos arcPagos ("Pagos.dat");

//Guardo una cantidad actual p/ poder revertir si algo  falla
int cantidadPedidosPrevios = arcPedido.contarRegistros();

//Guardo la cantidad actual de detallesPedidos por si algo falla
int cantidadDetallesInicial = arcDetalle.contarRegistros();



cout << "-------- REALIZAR NUEVO PEDIDO --------"<<endl;

//Verifico que existan clientes activos antes de continuar
if (!arcCliente.hayClientesConEstadoEliminado(false)){
    cout << "No hay clientes activos para generar pedidos."<<endl;
    cout<<endl;
    return;
}

cout << endl << "CLIENTES DISPONIBLES: "<<endl;
arcCliente.listar();

//Valido el cin de idCliente
int idCliente = ingresarEntero("Seleccione el ID del Cliente para este pedido: ");


//Validar Cliente

int posCliente = arcCliente.buscarRegistro(idCliente);

//Existe el ID?

if(posCliente == -1){

    cout << "ERROR: El ID del cliente no existe. "<<endl;
    return;

}

//Está activo?
Cliente regCliente = arcCliente.leerRegistro(posCliente);
if (regCliente.getEliminado()== true){

    cout<< "ERROR: El cliente seleccionado se encuentra eliminado."<<endl;
    return;
}

//Si pasa esos dos if, el cliente es válido.

//Verifico si empleados activos p/ asignar el pedido
if(!arcEmpleado.hayEmpleadosConEstadoEliminado(false)){

    cout<< "No hay empleados disponibles para asignar el pedido."<<endl;
    return;
}

cout<< endl << "EMPLEADOS DISPONIBLES: "<<endl;
arcEmpleado.listar();

//Valido el cin de idEmpleado
cout<< endl;
int idEmpleado = ingresarEntero("Seleccione el ID del Empleado que atiende este pedido: ");



//Validación del EMPLEADO:
int posEmpleado = arcEmpleado.buscarRegistro(idEmpleado);

if (posEmpleado == -1){

    cout<< "ERROR: El ID del empleado no existe."<<endl;
    return;
}

Empleado regEmpleado = arcEmpleado.leerRegistro(posEmpleado);
if (regEmpleado.getEliminado()== true){

    cout << "ERROR: El empleado seleccionado se encuentra eliminado."<<endl;
    return;
}


//Si cliente y empleados son válidos se puede seguir

//CREAR PEDIDO
//creo obj Pedido vacío

Pedido regPedido;

int idNuevoPedido = cantidadPedidosPrevios + 1;


regPedido.Cargar(idNuevoPedido, idCliente, idEmpleado);

//Valido que haya productos activos p/ realizar el pedido
if(!arcProducto.hayProductosConEstadoEliminado(false)){
    cout << "No hay productos activos disponibles para armar el pedido."<<endl;
    cout<<endl;
    return;
}

//Bucle para agregar productos

cout << endl << "-------- AGREGAR PRODUCTOS AL PEDIDO --------" <<endl;

//Verifico que haya al menos un item antes de salir del bucle
bool seAgregoProducto = false;

while(true){

        cout<< endl << "PRODUCTOS DISPONIBLES: "<<endl;
        arcProducto.listar();

        //Valido el cin de idProducto
        cout <<endl;
        int idProducto = ingresarEntero("Seleccione el ID del Producto a agregar (0 para terminar):");


        //salir del bucle si el usuario ingresa 0.

        if (idProducto == 0){

                if(!seAgregoProducto){
                        char cancelar;
                cout<<"Aun no agrego productos. Desea cancelar el pedido? (S/N):";
                cin>> cancelar;
                if(cancelar == 'S' || cancelar == 's'){
                    arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial); //Vuelvo al estado original
                    cout << "Pedido cancelado antes de cargar productos."<<endl;
                    return;
                }
                system("cls");
                continue;

        }
            break;
        }

        //Validar producto
        //Buscar posición del producto
        int posicionProducto = arcProducto.buscarRegistro(idProducto);

        if(posicionProducto == -1){

            cout << "ERROR: El ID del producto no existe. Intente de nuevo."<<endl;
            system("pause");
            system("cls");
            continue; //salta al inicio del while(true) para volver a listar productos
        }

        //Leer el registro de productos para verificar el stock y estado
        Producto regProducto = arcProducto.leerRegistro(posicionProducto);


        //Validación, está eliminado?
        if (regProducto.getEliminado() == true) {
            cout << "ERROR: Ese producto (" << regProducto.getNombre() << ") ya no esta disponible (eliminado)." << endl;
            system("pause");
            system("cls");
            continue; // Salta al inicio del 'while(true)'
        }

        // Validacion, hay stock?
        if (regProducto.getStock()<=0){

            cout << "ERROR: PRODUCTO SIN STOCK ("<<regProducto.getNombre() <<")." <<endl;
            system("pause");
            system("cls");
            continue; // salta al inicio del while(true)
        }

        //PEDIR UNA CANTIDAD y validarla



        cout <<endl << "Producto seleccionado: "<< regProducto.getNombre()<<endl;
        cout << "Stock disponible: "<<regProducto.getStock()<<endl;

        //validacion del cin de ingresar entero
        cout <<endl;
        int cantidadPedida = ingresarEntero("Ingrese la cantidad deseada: ");

        if (cantidadPedida <=0){
            cout << "ERROR: La cantidad debe ser al menos de 1 (una) unidad."<<endl;
            system("pause");
            system("cls");
            continue; // Salta al inicio del while
        }


        if (cantidadPedida > regProducto.getStock()){

            cout << "ERROR: STOCK INSUFICIENTE. Hay "<<regProducto.getStock()<< "unidades disponibles."<<endl;
            system ( "pause");
            system ("cls");
            continue;
        }
//Pre-cálculo del costo de lo que se está intentando agregar ahora
float precioUnitario = regProducto.getPrecio();
float calculoSubtotalItem = precioUnitario * cantidadPedida;

//BÚSQUEDA SECUENCIAL: Verificosi este producto ya existe en este pedido específico.
// Retorna la posición en bytes o índice del registro en el archivo (o -1 si no existe).
int posicionDetalleExistente = arcDetalle.buscarDetallePorPedidoYProducto(idNuevoPedido, idProducto);

// Si el producto YA existe
if(posicionDetalleExistente != -1){

    // Lectura del registro original para saber cuántos había antes
    DetallePedido detalleExistente = arcDetalle.leerRegistro(posicionDetalleExistente);

    // Cálculo de la nueva cantidad total (Lo que había + lo nuevo)
    int cantidadAcumulada = detalleExistente.getCantidad() + cantidadPedida;

    //VALIDACIÓN DE STOCK
    if(cantidadAcumulada > regProducto.getStock()){
        cout<< "ERROR: La cantidad total solicitada supera el stock disponible."<<endl;
        system("pause");
        system("cls");

        continue;//  salta al inicio del bucle principal, pidiendo el producto de nuevo
    }

    //Actualización del objeto en memoria
    detalleExistente.setCantidad(cantidadAcumulada);


    // Si falla la escritura
    if(!arcDetalle.modificarRegistro(detalleExistente, posicionDetalleExistente)){
        cout<< "ERROR. No se pudo actualizar la cantidad del producto seleccionado."<<endl;
        // deshacer cambios si algo falla
        arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial);
        return;
    }

    // Actualizacion del subtotal general del pedido con el importe de los nuevos ítems
    regPedido.setSubtotal(regPedido.getSubtotal() + calculoSubtotalItem);
    seAgregoProducto = true; // Bandera para confirmar éxito


    cout<< "------------------------------------"<<endl;
    cout<<endl;
    cout<< "Cantidad de "<<regProducto.getNombre()<< " actualizada a "<<cantidadAcumulada<< " unidades."<<endl;
    cout<< "Subtotal acumulado del Pedido: $"<<regPedido.getSubtotal()<<endl;
    cout<< "------------------------------------"<<endl;
    cout<<endl;

    system("pause");
    system("cls");


    continue; //continue evita que el código siga bajando y cree un registro nuevo duplicado
}

        //Creación de DETALLEPEDIDO y actualizar subtotal

        DetallePedido regDetalle;

        int idDetalleNuevo = arcDetalle.contarRegistros() + 1;



        //cargar el objeto DetallePedido(le pasamos todos los datos)
        regDetalle.Cargar(idDetalleNuevo, idNuevoPedido, idProducto,cantidadPedida, precioUnitario);


        //Actualizar el subtotal del pedido principal en memoria
        float subtotalActual = regPedido.getSubtotal();
        regPedido.setSubtotal(subtotalActual + calculoSubtotalItem);


        cout << "-------------------------------------------------------"<<endl;
        cout << cantidadPedida << " unidades de "<<regProducto.getNombre()<< "agregadas."<<endl;
        cout << "Subtotal de este item: $"<<calculoSubtotalItem <<endl;
        cout << "Subtotal acumulado del Pedido: $"<<regPedido.getSubtotal()<<endl;
        cout << "-------------------------------------------------------"<<endl;


        //Grabar el detallepedido de disco
        bool exitoDetalle = arcDetalle.grabarRegistro(regDetalle);

        if (!exitoDetalle){

            cout << "ERROR: No se pudo grabar este item del detalle. Cancelando pedido..."<<endl;

            arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial);

            system("pause");
            return;
        }
        seAgregoProducto = true;
        system("pause");
        system ("cls");



}// Fin del while

cout << "---------- FIN DE LA CARGA DE PRODUCTOS ----------"<<endl;


// VALIDAR Y GRABAR EL PEDIDO PRINCIPAL

//Validar si se agregaron productos
if (regPedido.getSubtotal()== 0){
    cout << "Pedido cancelado (sin productos)."<<endl;
    arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial); //Restauro los detalles agregados en esta sesión
    return;
}

//Grabar el Pedido ppal de memoria al archivo
bool exitoPedido = arcPedido.grabarRegistro(regPedido);
if (!exitoPedido){

    cout << "ERROR. NO SE PUDO GRABAR EL PEDIDO PRINCIPAL."<<endl;

    arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial);
    return;
}

//CREAR Y GRABAR EL PAGO

//Creación de obj de Pago
Pagos regPago;

//Calculo del ID del nvo pago
int idPagoNuevo = arcPagos.contarRegistros() + 1;

//Obtener el monto total a pagar
float montoAPagar = regPedido.getTotal();

//Cargar el obj Pago
cout << endl << "----------REGISTRAR PAGO ----------"<<endl;
regPago.Cargar(idPagoNuevo, regPedido.getIdPedido(), montoAPagar);


//Grabo el Pago en el archivo
bool exitoPago = arcPagos.grabarRegistro(regPago);
if (!exitoPago){

    cout << "ERROR! El pedido se grabo, pero no se pudo registrar el Pago"<<endl;

    arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial);
    arcPedido.restaurarCantidadRegistros(cantidadPedidosPrevios);
    return;
}

//Actualizar Stock
cout <<endl << "Actualizando el stock de productos... "<<endl;

//Obtener el ID del pedido que acabo de guardar
int idPedidoActual = regPedido.getIdPedido();

//Cuento cuantos detalles hay en el archivo para poder recorrerlo
int cantDetalles = arcDetalle.contarRegistros();

//Recorro el archivo de Detalles

for (int i = 0; i<cantDetalles; i++){

    DetallePedido regDetalleLeido = arcDetalle.leerRegistro(i);

    //Verificar si el detalle se corresponde al pedido que acabo de hacer
    if (regDetalleLeido.getIdPedido() == idPedidoActual){


        //Si pertenece descontar el stock del producto correspondiente
        int idProctoADescontar = regDetalleLeido.getIdProducto();
        int cantidadVendida = regDetalleLeido.getCantidad();

        //Buscar la posición del producto en Productos.dat
        int posicionProducto = arcProducto.buscarRegistro(idProctoADescontar);

        if (posicionProducto != -1) {
                // Leer el registro del producto DESDE EL ARCHIVO
                Producto productoAModificar = arcProducto.leerRegistro(posicionProducto);

                // Calcular nuevo stock y actualizar el obj en RAM
                int stockActual = productoAModificar.getStock();
                productoAModificar.setStock(stockActual - cantidadVendida);

                // Sobreescribir el producto en el archivo con el nvo stock
                arcProducto.modificarRegistro(productoAModificar, posicionProducto);
            }

    }

}



cout << "Stock actualizado." <<endl;
cout << "------ PEDIDO COMPLETADO EXITOSAMENTE ------"<<endl;



}


void listarPedidos() {

//obj para la capa de Persistencia

ArchivoPedido arcPedido ("Pedidos.dat");

cout << "---------- LISTADO DE PEDIDOS (GENERAL) ----------"<<endl;

bool hayActivos = arcPedido.hayPedidosConEstado(false);
bool hayAnulados = arcPedido.hayPedidosConEstado(true);

if(!hayActivos && !hayAnulados){
    cout << "No hay pedidos cargados en el sistema."<<endl;
    return;
}

if(hayActivos){
    arcPedido.listarPorEstado(false);
}else {

    cout<<"No hay pedidos activos para mostrar" <<endl;
}
//Seccion de pedidos anulados
if(hayAnulados){
    arcPedido.listarPorEstado(true);
}else{
cout<< "No hay pedidos anulados."<<endl;
}

}


void verDetallePedido(){

//objs de persistencia necesarios
ArchivoPedido arcPedido("Pedidos.dat");
ArchivoDetallePedido arcDetalle("DetallesPedidos.dat");
ArchivoProducto arcProducto ("Productos.dat");
ArchivoPagos arcPagos("Pagos.dat");



cout << "---------- VER DETALLE DE PEDIDO ----------"<<endl;

cout << endl;
int idPedidoBuscar = ingresarEntero("Ingrese el ID del Pedido que desea ver: ");



//Buscar y validar el pedido principal
int posicionPedido = arcPedido.buscarRegistro(idPedidoBuscar);

if (posicionPedido == -1){

    cout << "ERROR: No se encontro un Pedido con ese ID."<<endl;
    return;

}

Pedido regPedido = arcPedido.leerRegistro(posicionPedido);

if (regPedido.getEliminado() == true){

    cout << "Este pedido se encuentra anulado. No se mostrara su detalle."<<endl;

}

cout << endl << "======================================"<<endl;
cout << "MOSTRANDO PEDIDO ID: "<< regPedido.getIdPedido()<<endl;
regPedido.Mostrar();

cout << endl << "---------- DETALLES DE PRODUCTOS ----------"<<endl;
int cantidadDetalles = arcDetalle.contarRegistros();
bool detallesEncontrados = false; //Bandera p/ saber si se encuentra al menos un detalle de producto pedido

for (int i = 0; i<cantidadDetalles; i++){
    DetallePedido regDetalleLeido = arcDetalle.leerRegistro(i);

    //Busco detalles que coincida con el ID del pedido
    if (regDetalleLeido.getIdPedido() == idPedidoBuscar){
        detallesEncontrados = true;

        //Obtengo el nombre del producto (en lugar de solo el ID)
        int posicionProducto = arcProducto.buscarRegistro(regDetalleLeido.getIdProducto()); //Cruce de dados entre el archivo Detalles y el archivo productos
        Producto regProducto = arcProducto.leerRegistro(posicionProducto);

        cout << "- Item: "<<regDetalleLeido.getIdDetalle()<<endl;
        cout << "  Producto: "<<regProducto.getNombre()<< " (ID: "<<regProducto.getIdProducto()<< ")"<<endl;
        cout << "  Cantidad: "<<regDetalleLeido.getCantidad() <<endl;
        cout << "  Precio Unitario: $" << regDetalleLeido.getPrecioUnitario()<< endl;

    }
}

if (!detallesEncontrados){
    cout << "Este pedido no tiene productos asociados: "<<endl;
}


cout << "---------- INFORMACION DEL PAGO ----------"<<endl;
int cantidadPagos = arcPagos.contarRegistros();
bool pagoEncontrado = false;

for (int i=0; i<cantidadPagos; i++){
    Pagos regPagoLeido = arcPagos.leerRegistro(i);

    //Busco el pago que coincida con el ID del pedido
    if (regPagoLeido.getIdPedido() ==idPedidoBuscar){
        regPagoLeido.Mostrar(); //Mostrar los datos del pago
        pagoEncontrado = true;
        break; // Salir del for porque un pedido tiene solo un pago
    }
}
if (!pagoEncontrado){
    cout << "Este pedido no tiene un pago asociado. "<<endl;
}

cout << "======================================"<<endl <<endl;


}

void anularPedido () {
    //Instancio los gestores de archivos que utilizaré
    ArchivoPedido arcPedido("Pedidos.dat");
    ArchivoDetallePedido arcDetalle("DetallesPedidos.dat");
    ArchivoProducto arcProducto ("Productos.dat");


    cout << "---------- ANULAR PEDIDO ----------"<<endl;

    if(!arcPedido.hayPedidosConEstado(false)){
        cout<< "No hay pedidos activos para anular."<<endl;
        return;
    }
    //Listo pedidos activos
    arcPedido.listarPorEstado(false);

    cout <<endl;
    int idAnular = ingresarEntero("Ingrese el ID del Pedido que desea anular: ");

    //Buscar y validar el Pedido ppal
    int posicionPedido = arcPedido.buscarRegistro(idAnular);

    if (posicionPedido == -1){
        cout << "ERROR: No se encontro un Pedido con ese ID."<<endl;
        return;
    }
    //Leo el obj en memoria
    Pedido regPedido = arcPedido.leerRegistro(posicionPedido);

    cout << "Pedido encontrado: "<<endl;
    regPedido.Mostrar();
    cout << endl;

    //Y si ya estaba anulado?
    if (regPedido.getEliminado() == true){

        cout << "Este pedido ya se encuentra anulado. "<<endl;
        return;
    }

    char confirmacion;
    cout << "Esta seguro que desea anular este pedido? (S/N)";
    cin >> confirmacion;

    if (confirmacion == 'S' || confirmacion == 's'){

        cout << "Devolviendo stock de productos... "<<endl;


        //Nucleo de la fn Restauraciónd de stock
        int cantidadDetalles = arcDetalle.contarRegistros();
        for (int i = 0; i < cantidadDetalles; i++){
            DetallePedido regDetalleLeido = arcDetalle.leerRegistro(i);

            if (regDetalleLeido.getIdPedido()==idAnular){

                int idProducto = regDetalleLeido.getIdProducto();
                int cantidadDevolver = regDetalleLeido.getCantidad();

                //Buscar el producto
                int posicionProducto = arcProducto.buscarRegistro(idProducto);

                if (posicionProducto != -1){

                    //Leer producto
                    Producto regProducto = arcProducto.leerRegistro(posicionProducto);

                    //Sumarle el stock devuelto
                    regProducto.setStock(regProducto.getStock() + cantidadDevolver);

                    //Sobreescribir el producto
                    arcProducto.modificarRegistro(regProducto, posicionProducto);
                }
            }
        }
        cout << "Stock devuelto."<<endl;

        //ANULAR PEDIDO (BAJA LOGICA)
        regPedido.setEliminado(true);//Actualiza el obj en RAM
        bool exito = arcPedido.modificarRegistro(regPedido, posicionPedido);

        if (exito){
            cout << "Pedido anulado exitosamente. "<<endl;

        }else {
                cout << "ERROR: No se pudo anular el pedido"<<endl;
        }


    } else {
                cout << "Operacion cancelada."<<endl;
    }

}
