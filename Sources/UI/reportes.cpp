#include<iostream>
#include<cstdio>

#include "../../Headers/UI/reportes.h"
//Entidades
#include "../../Headers/Entities/Pedido.h"
#include "../../Headers/Entities/DetallePedido.h"
#include "../../Headers/Entities/Cliente.h"
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/Entities/Producto.h"

//Archivos de persistencia
#include "../../Headers/Persistence/ArchivoPedido.h"
#include "../../Headers/Persistence/ArchivoDetallePedido.h"
#include "../../Headers/Persistence/ArchivoCliente.h"
#include "../../Headers/Persistence/ArchivoEmpleado.h"
#include "../../Headers/Persistence/ArchivoProducto.h"

#include "../../Headers/Utilidades/Validaciones.h"


using namespace std;



void menuReportes(){

while(true){
    system("cls");
    cout << "---------- MENU DE REPORTES ----------"<<endl;
    cout << "======================================"<<endl;

    cout << "1. Recaudacion Anual/Mensual"<<endl;
    cout << "2. Productos Mas Vendidos"<<endl;
    cout << "3. Ranking de clientes por Puntos"<<endl;
    cout << "4. Informe de Desempeno de Empleados"<<endl;
    cout << "5. Productos vendidos por periodo"<<endl;
    cout << "------------------------------------"<<endl;
    cout << "0. VOLVER AL MENU PRINCIPAL"<<endl;
    cout << "===================================="<<endl;
    cout <<endl;
    int opcion = ingresarEntero("SELECCIONE UNA OPCION: ");

    system("cls");

    switch(opcion){
case 1:
    reporteRecaudacionAnualMensual();
    break;
case 2:
    reporteProductosMasVendidos();
    break;
case 3:
    reporteRankingClientes();
    break;
case 4:
    reporteDesempenoEmpleados();
    break;
case 5:
    reporteProductosPorPeriodo();
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


void reporteRecaudacionAnualMensual(){

cout << "---------- REPORTE DE RECAUDACION ANUAL/MENSUAL ----------" <<endl;
cout <<endl;
int anioBuscado= ingresarEntero("Ingrese el anio que desea analizar: ");

//Creo el vector acumulador (uno por cada mes)
float vectorRecaudacionPorMes[12] = {0};



//Preparar los archivos necesarios
ArchivoPedido arcPedido ("Pedidos.dat");
int cantPedidos = arcPedido.contarRegistros();

//Recorro el archivo de Pedidos
for (int i=0; i< cantPedidos; i++){
    Pedido regPedido = arcPedido.leerRegistro(i);

    //Filtro por pedidos activos y del año solicitado
    if (regPedido.getEliminado()== false && regPedido.getFecha().getAnio() == anioBuscado ){

        //Obtener el mes
        int mes = regPedido.getFecha().getMes();

        //Obtener el total con descuento aplicado
        float totalVenta = regPedido.getTotal();

        //Acumular en el vector
        vectorRecaudacionPorMes[mes - 1] +=totalVenta;


    }
}

cout<<endl<< "RECAUDACION DEL ANIO " << endl;
cout << "============================="<<endl;
cout << "MES\t\tRECAUDACION"<<endl;
cout << "-----------------------------"<<endl;

const char* nombreMeses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

for (int i = 0; i<12; i++){

    cout <<nombreMeses[i]<< ": \t$" <<vectorRecaudacionPorMes[i]<<endl;
}

cout << "============================="<<endl;
}

//Función auxiliar p/ encontrar la posición del Mayor valor
//La uso en reporteProductosMasVendidos()

int buscarMaximoVector (int* vectorDeMaximo, int tam){

int posicionMaximo = 0;

for (int i= 1; i<tam; i++){

    if (vectorDeMaximo[i]> vectorDeMaximo[posicionMaximo]){
        posicionMaximo = i;
    }
}

return posicionMaximo;
}

void reporteProductosMasVendidos(){

//Archivos necesarios
ArchivoProducto arcProducto("Productos.dat");
ArchivoDetallePedido arcDetalle("DetallesPedidos.dat");

int cantidadProductos = arcProducto.contarRegistros();
int cantidadDetalles = arcDetalle.contarRegistros();

if (cantidadProductos == 0 || cantidadDetalles == 0){

    cout << "No hay suficientes datos de PRODUCTOS o  VENTAS para generar el reporte."<<endl;
    return;
}

//Creo el vector acumulador dinámico
//Pido memoria para un vector de enteros del tamaño de la cantidad de productos

int* vectorCantidadVendida = new int[cantidadProductos];
if (vectorCantidadVendida == nullptr){
    cout << "Error al asignar memoria."<<endl;
    return;
}


for (int i = 0; i<cantidadProductos; i++){
    vectorCantidadVendida[i] = 0;
}

//Leer y acumular ventas
for (int i = 0; i<cantidadDetalles; i++){
    DetallePedido regDetalle = arcDetalle.leerRegistro(i);

    int idProductoVendido = regDetalle.getIdProducto();
    int cantidadVendida = regDetalle.getCantidad();

    //Busco la posición de ese producto
    int posicionProducto = arcProducto.buscarRegistro(idProductoVendido);

    if (posicionProducto != -1 && posicionProducto < cantidadProductos) { //posicionProducto < cantidadProductos asegura de que la posición que encontramos (posicionProducto) esté dentro de los límites de nuestro vector

        Producto prod = arcProducto.leerRegistro(posicionProducto);

        // Filtro productos eliminados/inactivos
            if (!prod.getEliminado()) {
                vectorCantidadVendida[posicionProducto] += cantidadVendida;
            }
    }

}

cout << "--- REPORTE DE PRODUCTOS MAS VENDIDOS  ---" << endl;
cout << "=================================================" << endl;


    for (int i = 0; i < cantidadProductos; i++) {

        //LLamo a la fn auxiliar para encontrar la posicion del mas vendido
        int posicionMaximo = buscarMaximoVector(vectorCantidadVendida, cantidadProductos);

        //Verifico si el producto más vendido no tiene ventas
        if (vectorCantidadVendida[posicionMaximo] == 0) {
            break;
        }

        //Leo producto que está en esa posición ganadora
        Producto regProductoMax = arcProducto.leerRegistro(posicionMaximo);

        //Muestro el resultado
        cout << i + 1 << ". " << regProductoMax.getNombre();
        cout << " - " << vectorCantidadVendida[posicionMaximo] << " unidades." << endl;

        //Elimino a este ganador del vector acumulador poniendo su contador en -1 para que no vuelva a se el máximo en la siguiente vuelta del bucle
        vectorCantidadVendida[posicionMaximo] = -1;
    }

    cout << "=================================================" << endl;



    delete[] vectorCantidadVendida;

}

void reporteRankingClientes(){

system ("cls");
cout << "---------- RANKING DE CLIENTES POR PUNTOS DE FIDELIDAD ----------"<<endl;

ArchivoCliente arcCliente("Clientes.dat");
int cantidadClientes = arcCliente.contarRegistros();

if (cantidadClientes == 0){

    cout << "No hay registros de CLIENTES para generar el reporte."<<endl;
    system ("pause");
    return;
}

//Pido memoria dinámica p/ copiar los clientes
Cliente* vectorClientes = new Cliente[cantidadClientes];

if (vectorClientes == nullptr){

    cout << "ERROR: No se pudo asignar memoria para generar el reporte."<<endl;
    system ("pause");
    return;

}

//Cargo los clientes activos y no eliminados en el vector
int cantidadValidados = 0;

for (int i = 0; i<cantidadClientes; i++){
    Cliente reg = arcCliente.leerRegistro(i);

    if (reg.getId() != -1 && reg.getEliminado()== false){
        vectorClientes[cantidadValidados] = reg;
        cantidadValidados++;
    }
}

//Si no hay clientes activos?
if (cantidadValidados == 0){

    cout << "No hay CLIENTES activos para mostrar en el ranking."<<endl;
    delete[] vectorClientes;
    system("pause");
    return;
}

//Ordeno el vector de mayor a menor (burbujeo)
for (int i=0; i<cantidadValidados - 1; i++){
    for (int j = i +1; j<cantidadValidados; j++){
        if (vectorClientes[i].getPuntosFidelidad() < vectorClientes[j].getPuntosFidelidad()){

            Cliente aux = vectorClientes[i];
            vectorClientes[i] = vectorClientes[j];
            vectorClientes[j] = aux;
        }
    }
}

    cout << "POS\tID\tAPELLIDO\t\tNOMBRE\t\tPUNTOS" << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (int i = 0; i<cantidadValidados; i++){

        cout << i + 1 << "\t"
        << vectorClientes[i].getId()<< "\t"
        << vectorClientes[i].getApellido()<< "\t\t"
        << vectorClientes[i].getNombre() << "\t\t"
        << vectorClientes[i].getPuntosFidelidad()<<endl;
    }

     cout << "-------------------------------------------------------------" << endl;
     cout << "Total de clientes activos: "<< cantidadValidados <<endl <<endl;

     delete []vectorClientes;

     system("pause");


}


void reporteDesempenoEmpleados() {

    system("cls");

    cout << "---------- REPORTE DE DESEMPENO DE EMPLEADOS ----------" << endl;

    ArchivoEmpleado arcEmpleado("Empleados.dat");
    ArchivoPedido arcPedido("Pedidos.dat");

    int cantidadEmpleados = arcEmpleado.contarRegistros();
    int cantidadPedidos = arcPedido.contarRegistros();

    //Valido q haya pedidos y empleados
    if (cantidadEmpleados == 0 || cantidadPedidos == 0) {
        cout << "No hay suficientes registros de EMPLEADOS o PEDIDOS para generar el reporte." << endl;
        system("pause");
        return;
    }

    //Reservo memoria dinámica para empleados
    Empleado* vectorEmpleados = new Empleado[cantidadEmpleados];
    if (vectorEmpleados == nullptr) {
        cout << "ERROR: No se pudo asignar memoria para los empleados." << endl;
        system("pause");
        return;
    }

    //Cargo los empleados activos
    int cantidadValidos = 0;
    for (int i = 0; i < cantidadEmpleados; i++) {
        Empleado reg = arcEmpleado.leerRegistro(i);
        if (reg.getId() != -1 && reg.getEliminado() == false) {
            vectorEmpleados[cantidadValidos] = reg;
            cantidadValidos++;
        }
    }

    if (cantidadValidos == 0) {
        cout << "No hay EMPLEADOS activos para realizar el reporte." << endl;
        delete[] vectorEmpleados;
        system("pause");
        return;
    }

    //Creo el vector acumulador p/ pedidos
    int* vectorCantidadPedidos = new int[cantidadValidos];
    if (vectorCantidadPedidos == nullptr) {
        cout << "ERROR: No se pudo asignar memoria para el acumulador de pedidos." << endl;
        delete[] vectorEmpleados;
        system("pause");
        return;
    }

    //Inicializo el vector acumulador
    for (int i = 0; i < cantidadValidos; i++) {
        vectorCantidadPedidos[i] = 0;
    }

    //Recorro los pedidos y acumular por empleado
    for (int i = 0; i < cantidadPedidos; i++) {
        Pedido regPedido = arcPedido.leerRegistro(i);

        if (regPedido.getEliminado() == false) {
            //Obtengo el ID del empleado que atendió el pedido
            int idEmpleadoPedido = regPedido.getIdEmpleado();

            //Busco el empleado correspondiente
            for (int j = 0; j < cantidadValidos; j++) {
                if (vectorEmpleados[j].getId() == idEmpleadoPedido) {
                    vectorCantidadPedidos[j]++;
                    break;
                }
            }
        }
    }

    //Ordeno los dos vectores con burbujeo
    for (int i = 0; i < cantidadValidos - 1; i++) {
        for (int j = i + 1; j < cantidadValidos; j++) {
            if (vectorCantidadPedidos[i] < vectorCantidadPedidos[j]) {
                int auxCant = vectorCantidadPedidos[i];
                vectorCantidadPedidos[i] = vectorCantidadPedidos[j];
                vectorCantidadPedidos[j] = auxCant;

                Empleado auxEmp = vectorEmpleados[i];
                vectorEmpleados[i] = vectorEmpleados[j];
                vectorEmpleados[j] = auxEmp;
            }
        }
    }

    //Muestro el reporte
    cout << endl;
    cout << "POS\tID\tAPELLIDO\t\tNOMBRE\t\tPEDIDOS ATENDIDOS" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (int i = 0; i < cantidadValidos; i++) {
        cout << i + 1 << "\t"
             << vectorEmpleados[i].getId() << "\t"
             << vectorEmpleados[i].getApellido() << "\t\t"
             << vectorEmpleados[i].getNombre() << "\t\t"
             << vectorCantidadPedidos[i] << endl;
    }

    cout << "---------------------------------------------------------------" << endl;
    cout << "Total de empleados activos: " << cantidadValidos << endl << endl;

    //Libero la memoria
    delete[] vectorCantidadPedidos;
    delete[] vectorEmpleados;

    system("pause");
}

void reporteProductosPorPeriodo(){
    system("cls");
    cout << "---------- REPORTE DE PRODUCTOS VENDIDOS POR PERIODOS ----------" << endl;

    //Pido fechas al usuario
    Fecha fechaDesde, fechaHasta;

    cout << "Ingrese la FECHA DESDE: " << endl;
    fechaDesde.Cargar();

    cout << "Ingrese la FECHA HASTA: " << endl;
    fechaHasta.Cargar();

    //Valido que la fecha hasta no sea anterior a la de "desde"
    //Utilizo la sobrecarga de operadores en la clase Fecha, para comparar objetos Fecha directamente con "<" o ">".
    if (fechaHasta < fechaDesde) {
        cout << "ERROR: La fecha final no puede ser anterior a la fecha inicial." << endl;
        system("pause");
        return;
    }

    //Abro los archivos que necesito
    ArchivoProducto arcProducto("Productos.dat");
    ArchivoDetallePedido arcDetalle("DetallesPedidos.dat");
    ArchivoPedido arcPedido("Pedidos.dat");

    int cantidadProductos = arcProducto.contarRegistros();
    int cantidadDetalles = arcDetalle.contarRegistros();

    if (cantidadProductos == 0 || cantidadDetalles == 0) {
        cout << "No hay suficientes datos de PRODUCTOS o VENTAS para generar el reporte." << endl;
        system("pause");
        return;
    }

    //Reservo memoria para los vectores
    Producto* vectorProductos = new Producto[cantidadProductos];
    if (vectorProductos == nullptr) {
        cout << "ERROR: No se pudo asignar memoria para los productos." << endl;
        system("pause");
        return;
    }

    int* vectorCantidadVendida = new int[cantidadProductos];
    if (vectorCantidadVendida == nullptr) {
        cout << "ERROR: No se pudo asignar memoria para el acumulador." << endl;
        delete[] vectorProductos;
        system("pause");
        return;
    }

    //Cargo productos activos y reseteo contador
    int cantidadValidos = 0;
    for (int i = 0; i < cantidadProductos; i++) {


        Producto reg = arcProducto.leerRegistro(i);

        if (reg.getIdProducto() != -1 && reg.getEliminado() == false) {
            vectorProductos[cantidadValidos] = reg;
            vectorCantidadVendida[cantidadValidos] = 0; //inicializo el contador
            cantidadValidos++;
        }
    }

    if (cantidadValidos == 0) {
        cout << "No hay PRODUCTOS activos para generar el reporte." << endl;
        delete[] vectorProductos;
        delete[] vectorCantidadVendida;
        system("pause");
        return;
    }

    //Recorro Detalle de pedidos y acumulo ventas
    int cantidadDetallesTotales = arcDetalle.contarRegistros();

    for (int i = 0; i < cantidadDetallesTotales; i++) {
        DetallePedido regDetalle = arcDetalle.leerRegistro(i);

        //Si el detalle pertenece a un pedido válido
        int idPedido = regDetalle.getIdPedido();

        //Busco el pedido correspondiente
        int posicionPedido = arcPedido.buscarRegistro(idPedido);
        if (posicionPedido == -1) continue; //si no lo encontró, salto

        Pedido regPedido = arcPedido.leerRegistro(posicionPedido);

        // Filtro: pedido no eliminado y dentro del rango de fechas
        //Las comparaciones se hacen directamente con operadores sobrecargados.
        if (regPedido.getEliminado() == false &&
            regPedido.getFecha() >= fechaDesde &&
            regPedido.getFecha() <= fechaHasta) {

            int idProductoDetalle = regDetalle.getIdProducto();
            int cantidadVendida = regDetalle.getCantidad();

            //Busco el producto dentro del vector de productos activos
            for (int j = 0; j < cantidadValidos; j++) {
                if (vectorProductos[j].getIdProducto() == idProductoDetalle) {
                    vectorCantidadVendida[j] += cantidadVendida;
                    break;
                }
            }
        }
    }

    //Ordeno los productos por cantidad vendida (burbujeo descendente)

    for (int i = 0; i < cantidadValidos - 1; i++) {
        for (int j = i + 1; j < cantidadValidos; j++) {
            if (vectorCantidadVendida[i] < vectorCantidadVendida[j]) {

                int auxCantidad = vectorCantidadVendida[i];
                vectorCantidadVendida[i] = vectorCantidadVendida[j];
                vectorCantidadVendida[j] = auxCantidad;

                Producto auxProducto = vectorProductos[i];
                vectorProductos[i] = vectorProductos[j];
                vectorProductos[j] = auxProducto;
            }
        }
    }

    //Muestro
    cout << endl;
    cout << "PERIODO: ";

    cout << fechaDesde.getDia() << "/" << fechaDesde.getMes() << "/" << fechaDesde.getAnio()
         << " - "
         << fechaHasta.getDia() << "/" << fechaHasta.getMes() << "/" << fechaHasta.getAnio() << endl;

    cout << "===============================================================" << endl;
    cout << "POS\tID\tPRODUCTO\t\tCANTIDAD VENDIDA" << endl;
    cout << "---------------------------------------------------------------" << endl;

    int totalGeneral = 0;
    for (int i = 0; i < cantidadValidos; i++) {
        if (vectorCantidadVendida[i] > 0) {
            cout << i + 1 << "\t"
                 << vectorProductos[i].getIdProducto() << "\t"
                 << vectorProductos[i].getNombre() << "\t\t"
                 << vectorCantidadVendida[i] << endl;

            totalGeneral += vectorCantidadVendida[i];
        }
    }

    cout << "---------------------------------------------------------------" << endl;
    cout << "TOTAL DE UNIDADES VENDIDAS EN EL PERIODO: " << totalGeneral << endl;

    //Libero la memoria dinámica utilizada
    delete[] vectorProductos;
    delete[] vectorCantidadVendida;

    system("pause");
}

