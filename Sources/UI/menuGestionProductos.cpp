#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>

#include "../../Headers/UI/menuGestionProductos.h"
#include "../../Headers/Entities/Producto.h"
#include "../../Headers/Persistence/ArchivoProducto.h"
#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;

// Filtros esperados por ArchivoProducto::listarConFiltro
const short FILTRO_ACTIVOS = 1;
const short FILTRO_ELIMINADOS = 2;
const short FILTRO_TODOS = 3;

void ordenarProductosPorNombre(Producto registros[], int cantidad);
void ordenarProductosPorPrecio(Producto registros[], int cantidad);
int seleccionarFiltroProductos();
void listarProductosDadosDeBaja();

void menuProductos() {

while (true) {
     system("cls");

    cout << "------- GESTION DE PRODUCTOS -------" <<endl;
    cout << "====================================" <<endl;
    cout << "1. AGREGAR PRODUCTO" <<endl;
    cout << "2. LISTAR PRODUCTOS" <<endl;
    cout << "3. LISTAR PRODUCTOS DADOS DE BAJA" <<endl;
    cout << "4. MODIFICAR PRODUCTO "<<endl;
    cout << "5. ELIMINAR PRODUCTO "<<endl;
    cout << "6. DAR DE ALTA PRODUCTO" <<endl;
    cout << "7. LISTAR PRODUCTOS ORDENADOS POR NOMBRE" <<endl;
    cout << "8. LISTAR PRODUCTOS ORDENADOS POR PRECIO" <<endl;
    cout << "9. CONSULTAR PRODUCTO POR ID" <<endl;
    cout << "10. CONSULTAR PRODUCTOS CON STOCK BAJO" <<endl;

    cout << "------------------------------------" <<endl;
    cout << "0. VOLVER AL MENU PRINCIPAL" <<endl;
    cout << "====================================" <<endl;
    cout <<endl;

    int opcion = ingresarEntero("SELECCIONE UNA OPCION: ");

    system ("cls");

    // Se controla la pausa manualmente para evitarla al volver al menú.
    bool mostrarPausa = true;

    switch (opcion){
case 1:
    agregarProducto();
    break;

case 2:
    listarProductos();
    break;

case 3:
    listarProductosDadosDeBaja();
    break;

case 4:
        modificarProducto();
        break;
case 5:
        bajaProducto();
        break;
case 6:
        altaProducto();
        break;
case 7:
        listarProductosOrdenadosPorNombre();
        break;
case 8:
        listarProductosOrdenadosPorPrecio();
        break;
case 9:
        consultarProductoPorID();
        break;
case 10:
        consultarProductosConStockBajo();
        break;

case 0:
    // No se muestra pausa cuando se elige volver.
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

int filtroSeleccionado = seleccionarFiltroProductos();

// Se delega la impresión en el archivo para reutilizar el formato de tabla.
arcProducto.listarConFiltro(filtroSeleccionado);
}

int seleccionarFiltroProductos(){

    cout << "Seleccione el filtro de productos a visualizar:"<<endl;
    cout << "1. Solo activos"<<endl;
    cout << "2. Solo dados de baja"<<endl;
    cout << "3. Todos"<<endl;

    int opcion;

    // Validamos la opción para evitar valores fuera de rango.
    do {
        opcion = ingresarEntero("Ingrese una opcion valida: ");
        if(opcion < 1 || opcion > 3){
            cout << "Opcion incorrecta. Intente nuevamente."<<endl;
        }
    } while(opcion < 1 || opcion > 3);

    return opcion;
}

void listarProductosDadosDeBaja(){

    ArchivoProducto arcProducto("Productos.dat");

    if(!arcProducto.hayProductosConEstadoEliminado(true)){
        cout << "No hay productos dados de baja para mostrar."<<endl;
        return;
    }

    cout << "--- LISTADO DE PRODUCTOS INACTIVOS (SOLO LECTURA) ---"<<endl;
    arcProducto.listarConFiltro(FILTRO_ELIMINADOS);



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

// Menú para elegir qué campo se desea modificar
cout << "¿Qué desea modificar?"<<endl;
cout << "1) Nombre"<<endl;
cout << "2) Precio"<<endl;
cout << "3) Stock"<<endl;
cout << "0) Cancelar"<<endl;

cout <<endl;
int opcionCampo;

// Validamos la opción para que esté dentro del rango permitido
do {
    opcionCampo = ingresarEntero("Ingrese una opcion: ");
    if(opcionCampo < 0 || opcionCampo > 3){
        cout << "Opcion incorrecta. Intente nuevamente."<<endl;
    }
} while(opcionCampo < 0 || opcionCampo > 3);

// Según la opción, pedimos solo ese dato. Esto evita repetir toda la carga.
switch(opcionCampo){

case 1:{
    // Se solicita únicamente el nombre y se valida que no quede vacío.
    char nuevoNombre[50];
    cout << "Ingrese el nuevo nombre: ";
    cargarCadena(nuevoNombre, 49);
    reg.setNombre(nuevoNombre);
    break;
}

case 2:{
    // ingresarFloat ya valida que el precio no sea negativo y repite la pregunta si corresponde.
    float nuevoPrecio = ingresarFloat("Ingrese el nuevo precio: ");
    reg.setPrecio(nuevoPrecio);
    break;
}

case 3:{
    int nuevoStock = ingresarEntero("Ingrese el nuevo stock: ");
    reg.setStock(nuevoStock);
    break;
}

case 0:
    cout << "Modificacion cancelada por el usuario."<<endl;
    return;
}


//Grabamos el registro de nuevo en el archivo solo con el campo elegido
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

void listarProductosOrdenadosPorNombre(){

ArchivoProducto arcProducto("Productos.dat");

int totalRegistros = arcProducto.contarRegistros();

if(totalRegistros == 0){

    cout << "No hay productos registrados para ordenar."<<endl;
    return;
}

Producto *registros = new Producto[totalRegistros];

int cantidadLeida = arcProducto.leerRegistros(registros, totalRegistros);

if(cantidadLeida == 0){

    cout << "No fue posible leer los productos almacenados."<<endl;
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

    cout << "No hay productos activos para mostrar."<<endl;
    delete [] registros;
    return;
}

ordenarProductosPorNombre(registros, cantidadActivos);

cout << "----- LISTADO ORDENADO POR NOMBRE -----"<<endl;

cout << left << setw(6) << "ID" << setw(30) << "Nombre" << setw(12) << "Precio" << setw(8) << "Stock" << endl;
cout << string(56, '-') << endl;


for(int i = 0; i < cantidadActivos; i++){
    registros[i].MostrarFila("ACTIVO");
}

cout << "--- FIN DEL LISTADO ---"<<endl;

delete [] registros;

}

void listarProductosOrdenadosPorPrecio(){

ArchivoProducto arcProducto("Productos.dat");

int totalRegistros = arcProducto.contarRegistros();

if(totalRegistros == 0){

    cout << "No hay productos registrados para ordenar."<<endl;
    return;
}

Producto *registros = new Producto[totalRegistros];

int cantidadLeida = arcProducto.leerRegistros(registros, totalRegistros);

if(cantidadLeida == 0){

    cout << "No fue posible leer los productos almacenados."<<endl;
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

    cout << "No hay productos activos para mostrar."<<endl;
    delete [] registros;
    return;
}

ordenarProductosPorPrecio(registros, cantidadActivos);

cout << "----- LISTADO ORDENADO POR PRECIO -----"<<endl;
cout << left << setw(6) << "ID" << setw(30) << "Nombre" << setw(12) << "Precio" << setw(8) << "Stock" << endl;
cout << string(56, '-') << endl;


for(int i = 0; i < cantidadActivos; i++){
    registros[i].MostrarFila("ACTIVO");
}

cout << "------------------ FIN DEL LISTADO --------------------------"<<endl;

delete [] registros;

}

void consultarProductoPorID(){

ArchivoProducto arcProducto("Productos.dat");

int totalRegistros = arcProducto.contarRegistros();

if(totalRegistros == 0){

    cout << "No hay productos registrados para consultar."<<endl;
    return;
}

cout << "----- CONSULTA DE PRODUCTO POR ID -----"<<endl;

int idBuscado = ingresarEntero("Ingrese el ID del producto a consultar: ");

int posicion = arcProducto.buscarRegistro(idBuscado);

if(posicion == -1){

    cout << "No se encontro ningun producto con ese ID."<<endl;
    return;
}

Producto reg = arcProducto.leerRegistro(posicion);

cout << "Producto encontrado:"<<endl;
reg.Mostrar();

if(reg.getEliminado()){
    cout << "Estado: Producto eliminado."<<endl;
} else {
    cout << "Estado: Producto activo."<<endl;
}

}

void consultarProductosConStockBajo(){

ArchivoProducto arcProducto("Productos.dat");

if(!arcProducto.hayProductosConEstadoEliminado(false)){

    cout << "No hay productos activos registrados para consultar."<<endl;
    return;
}

cout << "----- CONSULTA POR STOCK BAJO -----"<<endl;

int umbral;

do {
    umbral = ingresarEntero("Ingrese el valor de stock minimo a analizar: ");
    if(umbral < 0){
        cout << "El umbral debe ser mayor o igual a cero."<<endl;
    }
} while(umbral < 0);

int totalRegistros = arcProducto.contarRegistros();

if(totalRegistros == 0){

    cout << "No hay productos registrados para consultar."<<endl;
    return;
}

Producto *registros = new Producto[totalRegistros];

int cantidadLeida = arcProducto.leerRegistros(registros, totalRegistros);

if(cantidadLeida == 0){

    cout << "No fue posible leer los productos almacenados."<<endl;
    delete [] registros;
    return;
}

bool hayCoincidencias = false;
bool cabeceraMostrada = false;

cout << "Productos con stock por debajo de " << umbral << ":"<<endl;

for(int i = 0; i < cantidadLeida; i++){

    if(registros[i].getEliminado() == false && registros[i].getStock() < umbral){

    if(!cabeceraMostrada){
            cout << left << setw(6) << "ID" << setw(30) << "Nombre" << setw(12) << "Precio" << setw(8) << "Stock" << endl;
            cout << string(56, '-') << endl;
            cabeceraMostrada = true;
        }

        registros[i].MostrarFila("ACTIVO");
        hayCoincidencias = true;
    }
}

if(!hayCoincidencias){
    cout << "No se encontraron productos con stock menor al umbral indicado."<<endl;
}

delete [] registros;

}

void ordenarProductosPorNombre(Producto registros[], int cantidad){

//Burbujeo según el nombre del producto
for(int i = 0; i < cantidad - 1; i++){

    for(int j = i + 1; j < cantidad; j++){

       // strcmp > 0 significa: registros[i].getNombre() va DESPUÉS alfabéticamente que registros[j].getNombre().
       //Si esto pasa, entonces el producto que está en i debería estar después, así que lo intercambio.
        if(strcmp(registros[i].getNombre(), registros[j].getNombre()) > 0){

            //Intercambio de siempre en burbujejo
            Producto aux = registros[i];
            registros[i] = registros[j];
            registros[j] = aux;
        }
    }
}

}

void ordenarProductosPorPrecio(Producto registros[], int cantidad){

for(int i = 0; i < cantidad - 1; i++){

    for(int j = i + 1; j < cantidad; j++){

        if(registros[i].getPrecio() > registros[j].getPrecio()){
            Producto aux = registros[i];
            registros[i] = registros[j];
            registros[j] = aux;
        }
    }
}

}
