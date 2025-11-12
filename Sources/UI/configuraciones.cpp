#include<iostream>
#include <cstdio>
#include <cstring>
#include "../../Headers/UI/configuraciones.h"
#include "../../Headers/Entities/Cliente.h"
#include "../../Headers/Entities/Producto.h"
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/Entities/Pedido.h"
#include "../../Headers/Entities/DetallePedido.h"
#include "../../Headers/Entities/Pagos.h"
#include "../../Headers/Entities/Fecha.h"


using namespace std;

void menuConfiguraciones() {

int opcion;

while(true){
    system("cls");

    cout << "---------- MENU DE CONFIGURACIONES ----------"<<endl;
    cout << "============================================="<<endl;
    cout << "1. REALIZAR COPIA DE SEGURIDAD (.BKP)" <<endl;
    cout << "2. RESTAURAR COPIA DE SEGURIDAD (.BKP)" <<endl;
    cout << "3. EXPORTAR DATOS A FORMATO CSV" <<endl;
    cout << "---------------------------------------------"<<endl;
    cout << "0. VOLVER AL MENU PRINCIPAL"<<endl;
    cout << "============================================="<<endl;
    cout << "SELECCIONE UNA OPCION: ";
    cin >> opcion;

    system("cls");

    switch(opcion){
case 1:
    backupMenu();
    break;
case 2:
    restaurarCopiaSeguridad();
    break;
case 3:
    exportarDatosCSV();
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
//Helper para verificar si el archivo existe
bool existeArchivo( const char* nombreArchivo){
FILE* p = fopen(nombreArchivo, "rb");
if (p == nullptr){
    cout<< "NO EXISTE EL ARCHIVO"<<endl;
    return false;
}
fclose(p);
return true;

}

//Helper, da true si copió todo correctamente
bool copiarArchivoBinario( const char* origen, const char* destino){

FILE* in = fopen(origen, "rb");
if (in == nullptr){
    cout << "ERROR. No se pudo abrir el archivo de origen: "<<origen<<endl;
    return false;
}
FILE* out = fopen(destino, "wb");
if (out == nullptr){
    cout << "ERROR. No se pudo crear el archivo de destino: "<<destino<<endl;
    fclose(in);
    return false;
}

char byte;
while (fread(&byte, sizeof(byte), 1, in)==1){

    fwrite(&byte, sizeof(byte), 1, out);
}

fclose(in);
fclose(out);

return true;

}


void backupMenu() {

    int opcion;

    while (true) {

        system("cls");
        cout << "---------- COPIA DE SEGURIDAD ----------" << endl;
        cout << "========================================" << endl;
        cout << "1. Respaldar CLIENTES" << endl;
        cout << "2. Respaldar PRODUCTOS" << endl;
        cout << "3. Respaldar EMPLEADOS" << endl;
        cout << "4. Respaldar PEDIDOS" << endl;
        cout << "5. Respaldar DETALLES DE PEDIDOS" << endl;
        cout << "6. Respaldar PAGOS" << endl;
        cout << "----------------------------------------" << endl;
        cout << "7. RESPALDAR TODOS LOS ARCHIVOS" << endl;
        cout << "----------------------------------------" << endl;
        cout << "0. VOLVER AL MENU ANTERIOR" << endl;
        cout << "========================================" << endl;
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;

        if (opcion == 0) return;

        char origen[50];
        char destino[50];

        switch (opcion) {

        case 1:
            strcpy(origen, NOMBRE_ARCH_CLIENTES);
            strcpy(destino, "Clientes.bkp");
            break;

        case 2:
            strcpy(origen, NOMBRE_ARCH_PRODUCTOS);
            strcpy(destino, "Productos.bkp");
            break;

        case 3:
            strcpy(origen, NOMBRE_ARCH_EMPLEADOS);
            strcpy(destino, "Empleados.bkp");
            break;

        case 4:
            strcpy(origen, NOMBRE_ARCH_PEDIDOS);
            strcpy(destino, "Pedidos.bkp");
            break;

        case 5:
            strcpy(origen, NOMBRE_ARCH_DETALLES);
            strcpy(destino, "DetallesPedidos.bkp");
            break;

        case 6:
            strcpy(origen, NOMBRE_ARCH_PAGOS);
            strcpy(destino, "Pagos.bkp");
            break;

        case 7:
            // Backup general
            copiarArchivoBinario(NOMBRE_ARCH_CLIENTES, "Clientes.bkp");
            copiarArchivoBinario(NOMBRE_ARCH_PRODUCTOS, "Productos.bkp");
            copiarArchivoBinario(NOMBRE_ARCH_EMPLEADOS, "Empleados.bkp");
            copiarArchivoBinario(NOMBRE_ARCH_PEDIDOS, "Pedidos.bkp");
            copiarArchivoBinario(NOMBRE_ARCH_DETALLES, "DetallesPedidos.bkp");
            copiarArchivoBinario(NOMBRE_ARCH_PAGOS, "Pagos.bkp");
            cout << "Se realizo el backup de todos los archivos correctamente." << endl;
            system("pause");
            continue;

        default:
            cout << "Opcion incorrecta." << endl;
            system("pause");
            continue;
        }

        // Valido existencia del archivo antes de copiar
        if (!existeArchivo(origen)) {
            cout << "No se encontro el archivo de origen: " << origen << endl;
        } else {
            bool exito = copiarArchivoBinario(origen, destino);
            if (exito) {
                cout << "Backup creado correctamente: " << destino << endl;
            } else {
                cout << "ERROR al crear el backup." << endl;
            }
        }

        cout << endl;
        system("pause");
    }
}


void restaurarCopiaSeguridad(){

    int opcion;

    while(true) {

        system("cls");
        cout << "---------- RESTAURAR COPIA DE SEGURIDAD ----------" << endl;
        cout << "==================================================" << endl;
        cout << "1. Restaurar CLIENTES" << endl;
        cout << "2. Restaurar PRODUCTOS" << endl;
        cout << "3. Restaurar EMPLEADOS" << endl;
        cout << "4. Restaurar PEDIDOS" << endl;
        cout << "5. Restaurar DETALLES DE PEDIDOS" << endl;
        cout << "6. Restaurar PAGOS" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "7. RESTAURAR TODOS LOS ARCHIVOS" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "0. VOLVER AL MENU ANTERIOR" << endl;
        cout << "==================================================" << endl;
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;

        if(opcion == 0) return;

        char origen[50];
        char destino[50];

        switch (opcion){

        case 1:
            strcpy(origen, "Clientes.bkp");
            strcpy(destino, NOMBRE_ARCH_CLIENTES);
            break;

        case 2:
            strcpy(origen, "Productos.bkp");
            strcpy(destino, NOMBRE_ARCH_PRODUCTOS);
            break;

        case 3:
            strcpy(origen, "Empleados.bkp");
            strcpy(destino, NOMBRE_ARCH_EMPLEADOS);
            break;

        case 4:
            strcpy(origen, "Pedidos.bkp");
            strcpy(destino, NOMBRE_ARCH_PEDIDOS);
            break;

        case 5:
            strcpy(origen, "DetallesPedidos.bkp");
            strcpy(destino, NOMBRE_ARCH_DETALLES);
            break;

        case 6:
            strcpy(origen, "Pagos.bkp");
            strcpy(destino, NOMBRE_ARCH_PAGOS);
            break;

    case 7:
        // Confirmar antes de restaurar todo
    char confirmarTodo;
    cout << "Esta seguro de restaurar todos los archivos del sistema? (S/N): ";
    cin >> confirmarTodo;

    if (confirmarTodo != 'S' && confirmarTodo != 's') {

        cout << "Operacion cancelada." << endl;
        system("pause");
        continue; // vuelve al menu sin restaurar

    }

        //Restaurar los archivos
        copiarArchivoBinario("Clientes.bkp", NOMBRE_ARCH_CLIENTES);
        copiarArchivoBinario("Productos.bkp", NOMBRE_ARCH_PRODUCTOS);
        copiarArchivoBinario("Empleados.bkp", NOMBRE_ARCH_EMPLEADOS);
        copiarArchivoBinario("Pedidos.bkp", NOMBRE_ARCH_PEDIDOS);
        copiarArchivoBinario("DetallesPedidos.bkp", NOMBRE_ARCH_DETALLES);
        copiarArchivoBinario("Pagos.bkp", NOMBRE_ARCH_PAGOS);

        cout << "Se restauraron todos los archivos correctamente." <<endl;
        system("pause");

        continue;

    default:
        cout << "Opcion incorrecta. Ingrese un numero valido."<<endl;
        system("pause");
        continue;

        }

        //Verifico si el archivo .bkp exitste antes de intentar restaurar
        if(!existeArchivo(origen)){
            cout << "No se encontro el archivo de backup: "<<origen<<endl;
        } else{
            char confirmacion;
            cout << "Esta seguro de sobreescribir el archivo original? (S/N): ";
            cin >> confirmacion;

            if(confirmacion == 'S' || confirmacion == 's') {

                bool exito = copiarArchivoBinario(origen, destino);

                if(exito){
                    cout << "Archivo restaurado correctamente: "<<destino <<endl;

                }else {
                    cout << "ERROR al restaurar el archivo."<<endl;
                }
            } else {
                    cout << "Operacion cancelada por el usuario."<<endl;
            }

        }
                cout << endl;
                system("pause");

    }

}

void exportarDatosCSV(){

    int opcion;

    while(true) {
             system("cls");

    cout << "---------- EXPORTAR DATOS A CSV ----------"<<endl;
    cout << "=========================================="<<endl;
    cout << "1. Exportar CLIENTES" <<endl;
    cout << "2. Exportar PRODUCTOS"<<endl;
    cout << "3. Exportar EMPLEADOS"<<endl;
    cout << "4. Exportar PEDIDOS"<<endl;
    cout << "5. Exportar DETALLES DE PEDIDOS"<<endl;
    cout << "6. Exportar PAGOS"<<endl;
    cout << "-------------------------------------------"<<endl;
    cout << "7. EXPORTAR TODOS"<<endl;
    cout << "-------------------------------------------"<<endl;
    cout << "0. VOLVER AL MENU ANTERIOR" <<endl;
    cout << "==========================================="<<endl;
    cout << "SELECCIONE UNA OPCION: ";
    cin >> opcion;

    if(opcion == 0) return;

    bool exitoExportacion = false;

    switch (opcion){

case 1:
    exitoExportacion = exportarClientesCSV("Clientes.csv");

    if (exitoExportacion == true){

        cout << "Clientes.csv generado correctamente."<<endl;
    }else {
     cout << "ERROR al generar Clientes.csv"<<endl;
    }
    break;


case 2:
    exitoExportacion = exportarProductosCSV("Productos.csv");
    if (exitoExportacion == true){

        cout<< "Productos.csv generado correctamente."<<endl;
    }else {
        cout << "ERROR al generar Productos.csv"<<endl;
    }
    break;

case 3:
    exitoExportacion = exportarEmpleadosCSV("Empleados.csv");
    if (exitoExportacion == true){

        cout<< "Empleados.csv generado correctamente."<<endl;
    }else {
        cout  << "ERROR al generar Empleados.csv"<<endl;
    }
    break;

case 4:
    exitoExportacion = exportarPedidosCSV("Pedidos.csv");
    if (exitoExportacion == true){

        cout << "Pedidos.csv generado correctamente."<<endl;
    }else {
        cout << "ERROR al generar Pedidos.csv"<<endl;
    }
    break;

case 5:
    exitoExportacion = exportarDetallesCSV("DetallesPedidos.csv");
    if (exitoExportacion == true){

        cout << "DetallesPedidos.csv generado correctamente."<<endl;

    } else {
        cout << "ERROR al generar DetallesPedidos.csv"<<endl;
    }
    break;

case 6:
    exitoExportacion = exportarPagosCSV("Pagos.csv");

    if (exitoExportacion == true){

        cout << "Pagos.csv generado correctamente."<<endl;
    }else {

        cout << "ERROR al generar Pagos.csv"<<endl;

    }
    break;

case 7: {

        bool exitoExportacionClientes = exportarClientesCSV("Clientes.csv");
        bool exitoExportacionProductos = exportarProductosCSV("Productos.csv");
        bool exitoExportacionEmpleados = exportarEmpleadosCSV("Empleados.csv");
        bool exitoExportacionPedidos = exportarPedidosCSV("Pedidos.csv");
        bool exitoExportacionDetalles = exportarDetallesCSV("DetallesPedidos.csv");
        bool exitoExportacionPagos = exportarPagosCSV("Pagos.csv");

        if (exitoExportacionClientes &&
            exitoExportacionProductos &&
            exitoExportacionEmpleados &&
            exitoExportacionPedidos &&
            exitoExportacionDetalles &&
            exitoExportacionPagos  ) {

                cout << "Se exportaron todos los archivos CSV correctamente."<<endl;
            } else {

            cout << "ERROR: Uno o mas archivos CSV no pudieron generarse."<<endl;
            }
            break;
    }

    default:
        cout << "Opcion incorrecta. Intente nuevamente. "<<endl;
        break;

        }
        cout << endl;
        system("pause");

    }
}

bool exportarClientesCSV(const char* csvDestino) {

    FILE* pDat = fopen("Clientes.dat", "rb");
    if (pDat == nullptr){

        cout << "ERROR: No se pudo abrir Clientes.dat"<<endl;
        return false;
    }

    FILE* pCsv = fopen(csvDestino, "w");
    if (pCsv == nullptr){

        cout<< "ERROR. No se pudo crear el archivo CSV."<<endl;
        fclose(pDat);
        return false;
    }

    //Encabezado del archivo CSV
    fprintf(pCsv, "ID,Nombre,Apellido,Telefono,PuntosFidelidad,Eliminado\n");//Escribe el texto formateado separado por comas

    Cliente reg;
    int contador = 0;

    //Lectura secuencial del archivo binario
    while(fread(&reg, sizeof(Cliente), 1, pDat)== 1){
        fprintf(pCsv, "%d, %s, %s, %s, %d, %d\n",
                reg.getId(),
                reg.getNombre(),
                reg.getApellido(),
                reg.getTelefono(),
                reg.getPuntosFidelidad(),
                reg.getEliminado());

        contador ++;
    }

    fclose(pDat);
    fclose(pCsv);

    if(contador == 0) {

        cout << "AVISO: No se encontraron registros en Clientes.dat"<<endl;
        return false;
    }

    return true;


    }

bool exportarProductosCSV(const char* csvDestino){

FILE* pDat = fopen("Productos.dat", "rb");
if (pDat == nullptr){

    cout << "ERROR: No se pudo abrir Productos.dat"<<endl;

    return false;
}

FILE* pCsv = fopen(csvDestino, "w");
if (pCsv = nullptr){

    cout<< "ERROR. No se pudo crear el archivo CSV."<<endl;

    fclose(pDat);
    return false;
}

fprintf(pCsv, "ID,Nombre,Precio,Stock,Eliminado\n");

Producto reg;
int contador = 0;

while(fread(&reg, sizeof(Producto), 1 ,pDat) == 1){

    fprintf(pCsv, "%d,%s,%.2f,%d,%d\n",
            reg.getIdProducto(),
            reg.getNombre(),
            reg.getPrecio(),
            reg.getStock(),
            reg.getEliminado());

    contador++;

}







}

bool exportarEmpleadosCSV(const char* csvDestino){

        FILE* pDat = fopen( "Empleados.dat", "rb");
        if (pDat == nullptr){
            cout << "ERROR: No se pudo abrir Empleados.dat"<<endl;

            return false;
        }

        FILE* pCsv = fopen(csvDestino, "w");
        if(pCsv == nullptr){
            cout << "ERROR. No se pudo crear el archivo CSV."<<endl;
            fclose(pDat);
            return false;
        }

        //Encabezado del CSV
        fprintf(pCsv, "ID,Nombre,Apellido,Puesto,Eliminado\n");


        Empleado reg;
        int contador = 0;

        //Lectura secuencial de los registros
        while(fread(&reg, sizeof(Empleado), 1, pDat) == 1){

            fprintf(pCsv, "%d,%s,%s,%s,%d\n",

                    reg.getId(),
                    reg.getNombre(),
                    reg.getApellido(),
                    reg.getPuesto(),
                    reg.getEliminado());

                contador++;
        }
fclose(pDat);
fclose(pCsv);

if(contador==0){

    cout << "Aviso: No se encontraron registros en Empleados.dat"<<endl;
    return false;
}

return true;
    }

bool exportarPedidosCSV(const char* csvDestino){

FILE* pDat = fopen("Pedidos.dat", "rb");

if(pDat == nullptr){

    cout << "ERROR: No se pudo abrir Pedidos.dat"<<endl;
    return false;
}

FILE* pCsv = fopen(csvDestino, "w");
if (pCsv == nullptr){

    cout << "ERROR. No se pudo crear el archivo CSV."<<endl;
    fclose(pDat);
    return false;
}

//Encabezado CSV
fprintf(pCsv, "ID_Pedido,ID_Cliente,ID_Empleado,Nro_Mesa,Fecha_Dia,Fecha_Mes,Fecha_Anio,Subtotal,Descuento,Puntuacion,Eliminado\n");

Pedido reg;
int contador = 0;

//Lectura secuencial del archivo
while (fread(&reg, sizeof(Pedido), 1, pDat) == 1){

    Fecha f = reg.getFecha();

    fprintf(pCsv, "%d,%d,%d,%d,%d,%d,%d,%.2f,%d,%d,%d\n",
                reg.getIdPedido(),
                reg.getIdCliente(),
                reg.getIdEmpleado(),
                reg.getNroMesa(),
                f.getDia(),
                f.getMes(),
                f.getAnio(),
                reg.getSubtotal(),
                reg.getPorcentajeDescuento(),
                reg.getPuntuacionServicio(),
                reg.getEliminado());



    contador++;


}

fclose(pDat);
fclose(pCsv);

if (contador == 0){

    cout << "Aviso: No se encontraron registros en Pedidos.dat"<<endl;
    return false;
}

return true;

}

bool exportarDetallesCSV( const char* csvDestino){

FILE* pDat = fopen("DetallesPedidos.dat", "rb");

if (pDat == nullptr){

    cout << "ERROR: No se pudo abrir DetallesPedidos.dat"<<endl;
    return false;
}


FILE* pCsv = fopen(csvDestino, "w");
if (pCsv == nullptr) {
    cout << "ERROR: No se pudo crear el archivo CSV."<<endl;
    fclose(pDat);
    return false;
}

//Encabezado CSV
fprintf(pCsv, "ID_Detalle,ID_Pedido,ID_Producto,Cantidad,Precio_Unitario,Subtotal\n");


DetallePedido reg;
int contador = 0;

//Lectura secuencial
while (fread(&reg, sizeof(DetallePedido), 1, pDat)==1){


    //Calculo el subtotal en tiempo de exportacion
    float subtotal = reg.getCantidad()* reg.getPrecioUnitario();


    fprintf(pCsv, "%d,%d,%d,%d,%.2f,%.2f\n",
            reg.getIdDetalle(),
            reg.getIdPedido(),
            reg.getIdProducto(),
            reg.getCantidad(),
            reg.getPrecioUnitario(),
            subtotal );

     contador++;
}

fclose(pDat);
fclose (pCsv);

if (contador == 0){

    cout << "Aviso: No se encontraron registros en DetallesPedidos.dat"<<endl;
    return false;
}

return true;


}

bool exportarPagosCSV(const char* csvDestino){

FILE* pDat = fopen("Pagos.dat", "rb");
if (pDat == nullptr){

    cout << "ERROR: No se pudo abrir Pagos.dat"<<endl;
    return false;
}

FILE* pCsv = fopen(csvDestino, "w");
if (pCsv == nullptr){

    cout << "ERROR: No se pudo crear el archivo CSV."<<endl;
    fclose(pDat);
    return false;
}

//Encabezado del CSV
fprintf(pCsv, "ID_Pago,ID_Pedido,Fecha_Dia,Fecha_Mes,Fecha_Anio,Metodo_Pago,Monto_Pagado\n");

Pagos reg;
int contador = 0;


//Lectura secuencial del archivo
while(fread(&reg, sizeof(Pagos), 1, pDat) == 1){

        //Obtengo la fecha de pago
        Fecha f = reg.getFechaPago();

        //Determino el método de pago como texto
        const char* metodoTexto;

        switch(reg.getMetodoPago()){
        case 1: metodoTexto = "Efectivo"; break;
        case 2: metodoTexto = "Tarjeta"; break;
        case 3: metodoTexto = "Transferencia"; break;
        default: metodoTexto = "Desconocido"; break;

        }

    fprintf(pCsv, "%d,%d,%d,%d,%d,%s,%.2f\n",
                reg.getIdPago(),
                reg.getIdPedido(),
                f.getDia(),
                f.getMes(),
                f.getAnio(),
                metodoTexto,
                reg.getMontoPagado());

    contador++;
}

fclose(pDat);
fclose(pCsv);

if (contador == 0) {

    cout << "Aviso: No se encontraron registros en Pagos.dat"<<endl;
    return false;
}

return true;





}




















