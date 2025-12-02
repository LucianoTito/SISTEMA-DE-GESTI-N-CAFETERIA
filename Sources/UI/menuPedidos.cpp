#include<iostream>
#include <cstdlib>

#include "../../Headers/UI/menuPedidos.h"
#include "../../Headers/Entities/Cliente.h"
#include "../../Headers/Persistence/ArchivoCliente.h"
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/Persistence/ArchivoEmpleado.h"
#include "../../Headers/Entities/Producto.h"
#include "../../Headers/Persistence/ArchivoProducto.h"
#include "../../Headers/Entities/Pedido.h"
#include "../../Headers/Entities/Fecha.h"
#include "../../Headers/Persistence/ArchivoPedido.h"
#include "../../Headers/Entities/DetallePedido.h"
#include "../../Headers/Persistence/ArchivoDetallePedido.h"
#include "../../Headers/Entities/Pagos.h"
#include "../../Headers/Persistence/ArchivoPagos.h"
#include "../../Headers/Utilidades/Validaciones.h"
using namespace std;

//Funciones auxiliares privadas de este módulo
void ordenarPedidosPorFecha(Pedido vectorPedidos[], int cantidad);
void mostrarResumenPedido(Pedido pedido);
void menuConsultasPedidos();
void consultaPedidosPorRangoFechas();
void consultaPedidosPorCliente();
void consultaPedidosPorEmpleado();

void menuPedidos(){

int opcion;
while (true){
    system ("cls");

    cout << "---------- GESTION DE PEDIDOS ----------" <<endl;
    cout << "========================================" <<endl;
    cout << "1. REALIZAR UN PEDIDO "<< endl;
    cout << "2. VER DETALLE DE UN PEDIDO" <<endl;
    cout << "3. LISTAR PEDIDOS (ORDENADOS POR FECHA)" <<endl;
    cout << "4. CONSULTAS DE PEDIDOS" <<endl;
    cout << "5. ANULAR UN PEDIDO "<<endl; //baja logica
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
     menuConsultasPedidos();
    break;
case 5:
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
                cout<<"Aun no agrego productos. Desea cancelar el pedido? (S/N): ";
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


//BÚSQUEDA SECUENCIAL: Verifico si este producto ya existe en este pedido específico.
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

    //Pre-cálculo del costo de lo que se está intentando agregar ahora
float precioUnitario = regProducto.getPrecio();
 float calculoSubtotalItem = precioUnitario * cantidadPedida;


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



        int idDetalleNuevo = arcDetalle.contarRegistros() + 1;

        float precioUnitario = 0.0f;
        while(true){
            cout << endl << "Precio sugerido del sistema: $"<<regProducto.getPrecio()<<endl;
            precioUnitario = ingresarFloat("Ingrese el precio unitario a aplicar: ");
            if(precioUnitario >= 0){
                break;
            }
            cout << "ERROR: El precio unitario no puede ser negativo."<<endl;
        }

        float calculoSubtotalItem = precioUnitario * cantidadPedida;

 //Crear el objeto DetallePedido con los datos validados
        DetallePedido regDetalle(
            idDetalleNuevo,
            idNuevoPedido,
            idProducto,
            cantidadPedida,
            precioUnitario
        );
cout << endl;
        cout << "ID Detalle asignado: "<<regDetalle.getIdDetalle()<<endl;
        cout << "ID Pedido asociado: "<<regDetalle.getIdPedido()<< endl;
        cout <<"ID Producto asociado: "<<regDetalle.getIdProducto()<<endl;
        cout << "Cantidad registrada: "<< regDetalle.getCantidad() << endl;
        cout << "Precio unitario registrado: $"<< regDetalle.getPrecioUnitario() << endl;


        //Actualizar el subtotal del pedido principal en memoria
        float subtotalActual = regPedido.getSubtotal();
        regPedido.setSubtotal(subtotalActual + calculoSubtotalItem);


        cout << "-------------------------------------------------------"<<endl;
        cout << cantidadPedida << " unidades de "<<regProducto.getNombre()<< " agregadas."<<endl;
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

//Cargar el obj Pago (con validación de coherencia de fechas)
cout << endl << "----------REGISTRAR PAGO ----------"<<endl;
regPago.Cargar(idPagoNuevo, regPedido.getIdPedido(), montoAPagar, regPedido.getFecha());



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

cout << "---------- LISTADO DE PEDIDOS ORDENADOS POR FECHA ----------"<<endl;

int cantidadRegistros = arcPedido.contarRegistros();

if(cantidadRegistros == 0){
    cout << "No hay pedidos cargados en el sistema."<<endl;
    return;
}
//Reservo memoria para copiar los pedidos y luego ordenarlos sin modificar el archivo
Pedido *vectorPedidos = new Pedido[cantidadRegistros];

int cantidadValidos = 0;

//Recorro el archivo copiando los pedidos existentes
for(int i=0; i<cantidadRegistros; i++){
    Pedido reg = arcPedido.leerRegistro(i);
    if(reg.getIdPedido() != -1){
        vectorPedidos[cantidadValidos] = reg;
        cantidadValidos++;
    }
}

if(cantidadValidos == 0){
    cout << "No se encontraron pedidos válidos para mostrar."<<endl;
    delete[] vectorPedidos;
    return;
}

//Ordeno el vector por fecha utilizando burbujeo
ordenarPedidosPorFecha(vectorPedidos, cantidadValidos);

bool hayActivos = false;
bool hayAnulados = false;

cout << endl << "------- PEDIDOS ACTIVOS -------" << endl;
for(int i=0; i<cantidadValidos; i++){
    if(vectorPedidos[i].getEliminado() == false){
        mostrarResumenPedido(vectorPedidos[i]);
        hayActivos = true;
    }
}

if(!hayActivos){
    cout << "No hay pedidos activos para mostrar."<<endl;
}

cout << endl << "------- PEDIDOS ANULADOS -------" << endl;
for(int i=0; i<cantidadValidos; i++){
    if(vectorPedidos[i].getEliminado() == true){
        mostrarResumenPedido(vectorPedidos[i]);
        hayAnulados = true;
    }
}

if(!hayAnulados){
    cout << "No hay pedidos anulados para mostrar."<<endl;
}

cout << endl << "------- FIN DEL LISTADO -------" << endl;

delete[] vectorPedidos;

}

void menuConsultasPedidos(){

int opcion;

while(true){
    system("cls");
    cout << "---------- CONSULTAS DE PEDIDOS ----------"<<endl;
    cout << "========================================="<<endl;
    cout << "1. CONSULTAR POR RANGO DE FECHAS"<<endl;
    cout << "2. CONSULTAR POR CLIENTE"<<endl;
    cout << "3. CONSULTAR POR EMPLEADO"<<endl;
    cout << "-----------------------------------------"<<endl;
    cout << "0. VOLVER"<<endl;
    cout << "========================================="<<endl;

    opcion = ingresarEntero("SELECCIONE UNA OPCION: ");
    system("cls");

    switch(opcion){
    case 1:
        consultaPedidosPorRangoFechas();
        break;
    case 2:
        consultaPedidosPorCliente();
        break;
    case 3:
        consultaPedidosPorEmpleado();
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

void consultaPedidosPorRangoFechas(){

ArchivoPedido arcPedido("Pedidos.dat");

cout << "---------- CONSULTA DE PEDIDOS POR RANGO DE FECHAS ----------"<<endl;

if(!arcPedido.hayPedidosConEstado(false)){
    cout << "No hay pedidos activos cargados en el sistema."<<endl;
    return;
}

//Solicito las fechas al usuario
Fecha fechaDesde, fechaHasta;

cout << "Ingrese la FECHA DESDE:"<<endl;
fechaDesde.Cargar();

cout << endl << "Ingrese la FECHA HASTA:"<<endl;
fechaHasta.Cargar();

//Valido que la fecha hasta no sea anterior a la fecha desde
if(fechaHasta < fechaDesde){
    cout << "ERROR: La fecha final no puede ser anterior a la fecha inicial."<<endl;
    return;
}

int cantidadRegistros = arcPedido.contarRegistros();
int coincidencias = 0;

cout << endl;
cout << "Pedidos encontrados entre ";
cout << fechaDesde.getDia() << "/" << fechaDesde.getMes() << "/" << fechaDesde.getAnio();
cout << " y " << fechaHasta.getDia() << "/" << fechaHasta.getMes() << "/" << fechaHasta.getAnio() << endl;
cout << "-------------------------------------------------------------"<<endl;

// Recorro todos los pedidos para verificar cuáles se encuentran en el rango solicitado
for(int i=0; i<cantidadRegistros; i++){
    Pedido reg = arcPedido.leerRegistro(i);

    if(reg.getEliminado()==false &&
       reg.getFecha() >= fechaDesde &&
       reg.getFecha() <= fechaHasta){

        mostrarResumenPedido(reg);
        coincidencias++;
    }
}

if(coincidencias == 0){
    cout << "No se encontraron pedidos en el periodo indicado."<<endl;
}else{
    cout << "-------------------------------------------------------------"<<endl;
    cout << "Total de pedidos encontrados: "<< coincidencias << endl;
}

}

void consultaPedidosPorCliente(){

ArchivoCliente arcCliente("Clientes.dat");
ArchivoPedido arcPedido("Pedidos.dat");

cout << "---------- CONSULTA DE PEDIDOS POR CLIENTE ----------"<<endl;

if(!arcCliente.hayClientesConEstadoEliminado(false)){
    cout << "No hay clientes activos en el sistema."<<endl;
    return;
}

cout << endl << "CLIENTES ACTIVOS:"<<endl;
arcCliente.listar();

int idCliente = ingresarEntero("Ingrese el ID del cliente a consultar: ");

int posicionCliente = arcCliente.buscarRegistro(idCliente);

if(posicionCliente == -1){
    cout << "ERROR: El ID del cliente no existe."<<endl;
    return;
}

Cliente regCliente = arcCliente.leerRegistro(posicionCliente);

if(regCliente.getEliminado()){
    cout << "ERROR: El cliente seleccionado está eliminado."<<endl;
    return;
}

int cantidadRegistros = arcPedido.contarRegistros();
int coincidencias = 0;

cout << endl << "Pedidos asociados al cliente ID "<< idCliente << ":"<<endl;
cout << "-------------------------------------------------------------"<<endl;

// Filtro todos los pedidos del archivo por el ID del cliente seleccionado
for(int i=0; i<cantidadRegistros; i++){
    Pedido reg = arcPedido.leerRegistro(i);

    if(reg.getEliminado()==false && reg.getIdCliente() == idCliente){
        mostrarResumenPedido(reg);
        coincidencias++;
    }
}

if(coincidencias == 0){
    cout << "No se encontraron pedidos activos para este cliente."<<endl;
}else{
    cout << "-------------------------------------------------------------"<<endl;
    cout << "Total de pedidos del cliente: "<< coincidencias << endl;
}

}

void consultaPedidosPorEmpleado(){

ArchivoEmpleado arcEmpleado("Empleados.dat");
ArchivoPedido arcPedido("Pedidos.dat");

cout << "---------- CONSULTA DE PEDIDOS POR EMPLEADO ----------"<<endl;

if(!arcEmpleado.hayEmpleadosConEstadoEliminado(false)){
    cout << "No hay empleados activos para realizar la consulta."<<endl;
    return;
}

cout << endl << "EMPLEADOS ACTIVOS:"<<endl;
arcEmpleado.listar();

int idEmpleado = ingresarEntero("Ingrese el ID del empleado a consultar: ");

int posicionEmpleado = arcEmpleado.buscarRegistro(idEmpleado);

if(posicionEmpleado == -1){
    cout << "ERROR: El ID del empleado no existe."<<endl;
    return;
}

Empleado regEmpleado = arcEmpleado.leerRegistro(posicionEmpleado);

if(regEmpleado.getEliminado()){
    cout << "ERROR: El empleado seleccionado está eliminado."<<endl;
    return;
}

int cantidadRegistros = arcPedido.contarRegistros();
int coincidencias = 0;

cout << endl << "Pedidos atendidos por el empleado ID "<< idEmpleado << ":"<<endl;
cout << "-------------------------------------------------------------"<<endl;

for(int i=0; i<cantidadRegistros; i++){
    Pedido reg = arcPedido.leerRegistro(i);

    if(reg.getEliminado()==false && reg.getIdEmpleado() == idEmpleado){
        mostrarResumenPedido(reg);
        coincidencias++;
    }
}

if(coincidencias == 0){
    cout << "No se encontraron pedidos activos para este empleado."<<endl;
}else{

    cout << "-------------------------------------------------------------"<<endl;
    cout << "Total de pedidos atendidos: "<< coincidencias << endl;
}
}


//Ordeno el vector recibido por parámetro utilizando el campo Fecha. Aplico burbujeo
void ordenarPedidosPorFecha(Pedido vectorPedidos[], int cantidad){

    for(int i=0; i<cantidad-1; i++){
        for(int j=i+1; j<cantidad; j++){
            // Si la fecha del pedido j es anterior a la del pedido i, se intercambian posiciones
            if(vectorPedidos[j].getFecha() < vectorPedidos[i].getFecha()){
                Pedido aux = vectorPedidos[i];
                vectorPedidos[i] = vectorPedidos[j];
                vectorPedidos[j] = aux;
            }
        }
    }
}

//Muestra un resumen en una sola línea para facilitar la lectura de los listados
void mostrarResumenPedido(Pedido pedido){

    Fecha fecha = pedido.getFecha();

    cout << "ID: " << pedido.getIdPedido()
         << " | Fecha: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio()
         << " | Cliente: " << pedido.getIdCliente()
         << " | Empleado: " << pedido.getIdEmpleado()
         << " | Mesa: " << pedido.getNroMesa()
         << " | Total: $" << pedido.getTotal()
         << endl;
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

