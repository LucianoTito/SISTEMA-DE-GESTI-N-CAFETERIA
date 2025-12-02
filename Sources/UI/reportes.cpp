#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>

#include "../../Headers/UI/reportes.h"
#include "../../Headers/Entities/Pedido.h"
#include "../../Headers/Entities/DetallePedido.h"
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/Entities/Producto.h"
#include "../../Headers/Persistence/ArchivoPedido.h"
#include "../../Headers/Persistence/ArchivoDetallePedido.h"
#include "../../Headers/Persistence/ArchivoEmpleado.h"
#include "../../Headers/Persistence/ArchivoProducto.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Tablas.h"

using namespace std;

// ==========================================
// PROTOTIPOS AUXILIARES (PRIVADOS)
// ==========================================
// Estos helpers permiten cargar entidades en RAM para evitar la lentitud de leer disco en bucles.
Producto* cargarProductosActivos(int &cantidad);
Empleado* cargarEmpleadosActivos(int &cantidad);
int* cargarPedidosEnRango(Fecha desde, Fecha hasta, int &cantidad);

// Algoritmos de ordenamiento para los reportes
void ordenarRankingProductos(Producto* prods, int* cants, int n);
void ordenarRankingEmpleados(Empleado* emps, int* cants, int n);

// ==========================================
// MENU REPORTES
// ==========================================
void menuReportes(){
    int opcion;
    while(true){
        system("cls");
        lineaDoble(60);
        cout << "               MENU DE REPORTES Y ESTADISTICAS" << endl;
        lineaDoble(60);
        cout << "1. RECAUDACION MENSUAL (Por Anio)" << endl;
        cout << "2. RANKING PRODUCTOS MAS VENDIDOS (Historico)" << endl;
        cout << "3. DESEMPENIO DE EMPLEADOS (Cantidad de Pedidos)" << endl;
        cout << "4. PRODUCTOS VENDIDOS POR PERIODO (Fechas)" << endl;
        lineaSimple(60);
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        lineaDoble(60);

        opcion = ingresarEntero("SELECCIONE UNA OPCION: ");
        system("cls");

        switch(opcion){
            case 1: reporteRecaudacionAnualMensual(); break;
            case 2: reporteProductosMasVendidos(); break;
            case 3: reporteDesempenoEmpleados(); break;
            case 4: reporteProductosPorPeriodo(); break;
            case 0: return;
            default: cout << "Opcion incorrecta." << endl; break;
        }
        system("pause");
    }
}

// ==========================================
// 1. RECAUDACION ANUAL
// ==========================================
void reporteRecaudacionAnualMensual(){
    cout << "---------- REPORTE DE RECAUDACION ----------" << endl;
    int anio = ingresarEntero("Ingrese el anio a analizar: ");

    // Vector acumulador estatico (indices 0-11 representan Ene-Dic)
    float recaudacionMes[12] = {0};

    ArchivoPedido arcP("Pedidos.dat");
    int total = arcP.contarRegistros();

    // Recorrido secuencial del archivo de pedidos (Complejidad O(N))
    for(int i=0; i<total; i++){
        Pedido p = arcP.leerRegistro(i);
        // Filtramos solo pedidos activos y del año seleccionado
        if(!p.getEliminado() && p.getFecha().getAnio() == anio){
            int mes = p.getFecha().getMes();
            if(mes >= 1 && mes <= 12){
                // Sumamos al mes correspondiente
                recaudacionMes[mes - 1] += p.getTotal();
            }
        }
    }

    // --- Presentacion en Tabla ---
    cout << endl << "RECAUDACION DEL ANIO " << anio << endl;

    // Ajuste visual: Ancho 50 coincide con Tablas.cpp
    lineaDoble(50);
    imprimirFilaRecaudacion("MES", "TOTAL ($)");
    lineaSimple(50);

    const char* nombres[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                               "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    float totalAnual = 0;
    char sTotal[20];

    for(int i=0; i<12; i++){
        sprintf(sTotal, "$ %.2f", recaudacionMes[i]);
        imprimirFilaRecaudacion(nombres[i], sTotal);
        totalAnual += recaudacionMes[i];
    }

    lineaSimple(50);
    sprintf(sTotal, "$ %.2f", totalAnual);
    imprimirFilaRecaudacion("TOTAL ANUAL", sTotal);
    lineaDoble(50);
}

// ==========================================
// 2. PRODUCTOS MAS VENDIDOS
// ==========================================
void reporteProductosMasVendidos(){
    cout << "---------- RANKING DE PRODUCTOS (HISTORICO) ----------" << endl;

    // 1. CARGA EN MEMORIA (RAM)
    // Traemos todos los productos activos a un vector dinamico.
    // Esto optimiza el reporte porque la busqueda en RAM es mucho mas rapida que en disco.
    int cantProds = 0;
    Producto* productos = cargarProductosActivos(cantProds);
    if(productos == nullptr) return;

    // 2. VECTOR PARALELO
    // Creamos un vector de contadores del mismo tamanio que productos.
    // indice [i] del contador corresponde a productos[i].
    int* contadores = new int[cantProds];
    for(int i=0; i<cantProds; i++) contadores[i] = 0;

    // 3. PROCESAMIENTO
    ArchivoDetallePedido arcD("DetallesPedidos.dat");
    int totalDetalles = arcD.contarRegistros();

    for(int i=0; i<totalDetalles; i++){
        DetallePedido d = arcD.leerRegistro(i);

        // Busqueda Lineal en RAM para encontrar el producto vendido
        for(int k=0; k<cantProds; k++){
            if(productos[k].getIdProducto() == d.getIdProducto()){
                contadores[k] += d.getCantidad();
                break;
            }
        }
    }

    // 4. ORDENAMIENTO PARALELO
    ordenarRankingProductos(productos, contadores, cantProds);

    // 5. VISUALIZACION
    cout << endl;
    // Ajuste visual: Ancho 75
    lineaDoble(75);
    imprimirFilaRankingProductos("POS", "ID", "PRODUCTO", "VENDIDOS");
    lineaSimple(75);

    char sPos[5], sId[10], sCant[10];
    for(int i=0; i<cantProds; i++){
        if(contadores[i] > 0){
            sprintf(sPos, "%d", i+1);
            sprintf(sId, "%d", productos[i].getIdProducto());
            sprintf(sCant, "%d", contadores[i]);
            imprimirFilaRankingProductos(sPos, sId, productos[i].getNombre(), sCant);
        }
    }
    lineaDoble(75);

    // Liberamos memoria dinamica (importante en C++)
    delete[] productos;
    delete[] contadores;
}

// ==========================================
// 3. DESEMPENIO EMPLEADOS
// ==========================================
void reporteDesempenoEmpleados(){
    cout << "---------- RANKING DE EMPLEADOS ----------" << endl;

    // Misma logica: Carga en RAM -> Acumulacion -> Ordenamiento
    int cantEmps = 0;
    Empleado* empleados = cargarEmpleadosActivos(cantEmps);
    if(empleados == nullptr) return;

    int* contadores = new int[cantEmps];
    for(int i=0; i<cantEmps; i++) contadores[i] = 0;

    ArchivoPedido arcP("Pedidos.dat");
    int totalPedidos = arcP.contarRegistros();

    for(int i=0; i<totalPedidos; i++){
        Pedido p = arcP.leerRegistro(i);
        if(!p.getEliminado()){
            // Buscamos quien atendio el pedido
            for(int k=0; k<cantEmps; k++){
                if(empleados[k].getId() == p.getIdEmpleado()){
                    contadores[k]++;
                    break;
                }
            }
        }
    }

    ordenarRankingEmpleados(empleados, contadores, cantEmps);

    cout << endl;
    // Ajuste visual: Ancho 80 para nombres largos de empleados
    lineaDoble(80);
    imprimirFilaRankingEmpleados("POS", "ID", "APELLIDO", "NOMBRE", "PEDIDOS");
    lineaSimple(80);

    char sPos[5], sId[10], sCant[10];
    for(int i=0; i<cantEmps; i++){
        if(contadores[i] > 0){
            sprintf(sPos, "%d", i+1);
            sprintf(sId, "%d", empleados[i].getId());
            sprintf(sCant, "%d", contadores[i]);
            imprimirFilaRankingEmpleados(sPos, sId, empleados[i].getApellido(), empleados[i].getNombre(), sCant);
        }
    }
    lineaDoble(80);

    delete[] empleados;
    delete[] contadores;
}

// ==========================================
// 4. PRODUCTOS POR PERIODO
// ==========================================
void reporteProductosPorPeriodo(){
    cout << "---------- PRODUCTOS VENDIDOS POR PERIODO ----------" << endl;

    Fecha f1, f2;
    cout << "Desde: " << endl; f1.Cargar();
    cout << "Hasta: " << endl; f2.Cargar();

    if(f2 < f1){ cout << "Rango invalido." << endl; return; }

    // 1. FILTRADO PREVIO:
    // Generamos una lista SOLO con los IDs de pedidos validos en el rango.
    // Esto evita verificar fechas por cada item del detalle (muy costoso).
    int cantPedidosRango = 0;
    int* idsPedidosValidos = cargarPedidosEnRango(f1, f2, cantPedidosRango);

    if(cantPedidosRango == 0){
        cout << "No hay pedidos registrados en ese periodo." << endl;
        if(idsPedidosValidos) delete[] idsPedidosValidos;
        return;
    }

    int cantProds = 0;
    Producto* productos = cargarProductosActivos(cantProds);
    int* contadores = new int[cantProds];
    for(int i=0; i<cantProds; i++) contadores[i] = 0;

    ArchivoDetallePedido arcD("DetallesPedidos.dat");
    int totalDetalles = arcD.contarRegistros();

    for(int i=0; i<totalDetalles; i++){
        DetallePedido d = arcD.leerRegistro(i);

        // Verificamos si el pedido del detalle esta en nuestra lista "blanca"
        bool pedidoValido = false;
        for(int p=0; p<cantPedidosRango; p++){
            if(idsPedidosValidos[p] == d.getIdPedido()){
                pedidoValido = true;
                break;
            }
        }

        if(pedidoValido){
            // Acumular cantidad
            for(int k=0; k<cantProds; k++){
                if(productos[k].getIdProducto() == d.getIdProducto()){
                    contadores[k] += d.getCantidad();
                    break;
                }
            }
        }
    }

    ordenarRankingProductos(productos, contadores, cantProds);

    cout << endl;
    cout << "PERIODO: " << f1.getDia() << "/" << f1.getMes() << "/" << f1.getAnio()
         << " - " << f2.getDia() << "/" << f2.getMes() << "/" << f2.getAnio() << endl;

    // Ajuste visual: Ancho 75
    lineaDoble(75);
    imprimirFilaRankingProductos("POS", "ID", "PRODUCTO", "CANT.");
    lineaSimple(75);

    char sPos[5], sId[10], sCant[10];
    int totalGlobal = 0;
    int pos = 1;

    for(int i=0; i<cantProds; i++){
        if(contadores[i] > 0){
            sprintf(sPos, "%d", pos++);
            sprintf(sId, "%d", productos[i].getIdProducto());
            sprintf(sCant, "%d", contadores[i]);
            imprimirFilaRankingProductos(sPos, sId, productos[i].getNombre(), sCant);
            totalGlobal += contadores[i];
        }
    }
    lineaSimple(75);
    cout << "TOTAL UNIDADES VENDIDAS: " << totalGlobal << endl;
    lineaDoble(75);

    delete[] idsPedidosValidos;
    delete[] productos;
    delete[] contadores;
}

// ==========================================
// FUNCIONES DE CARGA Y ORDENAMIENTO (HELPERS)
// ==========================================

Producto* cargarProductosActivos(int &cantidad){
    ArchivoProducto arc("Productos.dat");
    int total = arc.contarRegistros();
    if(total == 0) { cout << "No hay productos." << endl; return nullptr; }

    Producto* temp = new Producto[total];
    cantidad = 0;
    for(int i=0; i<total; i++){
        Producto p = arc.leerRegistro(i);
        if(!p.getEliminado()) temp[cantidad++] = p;
    }
    return temp;
}

Empleado* cargarEmpleadosActivos(int &cantidad){
    ArchivoEmpleado arc("Empleados.dat");
    int total = arc.contarRegistros();
    if(total == 0) { cout << "No hay empleados." << endl; return nullptr; }

    Empleado* temp = new Empleado[total];
    cantidad = 0;
    for(int i=0; i<total; i++){
        Empleado e = arc.leerRegistro(i);
        if(!e.getEliminado()) temp[cantidad++] = e;
    }
    return temp;
}

int* cargarPedidosEnRango(Fecha desde, Fecha hasta, int &cantidad){
    ArchivoPedido arc("Pedidos.dat");
    int total = arc.contarRegistros();

    // Asignamos memoria para el peor caso (todos los pedidos)
    int* ids = new int[total];
    cantidad = 0;

    for(int i=0; i<total; i++){
        Pedido p = arc.leerRegistro(i);
        if(!p.getEliminado() && p.getFecha() >= desde && p.getFecha() <= hasta){
            ids[cantidad++] = p.getIdPedido();
        }
    }
    return ids;
}

// Ordenamiento burbujeo descendente (de mayor a menor)
void ordenarRankingProductos(Producto* prods, int* cants, int n){
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(cants[j] > cants[i]){
                // Intercambio de cantidades
                int auxC = cants[i]; cants[i] = cants[j]; cants[j] = auxC;
                // Intercambio de productos (para mantener la relacion indice-producto)
                Producto auxP = prods[i]; prods[i] = prods[j]; prods[j] = auxP;
            }
        }
    }
}

void ordenarRankingEmpleados(Empleado* emps, int* cants, int n){
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(cants[j] > cants[i]){
                int auxC = cants[i]; cants[i] = cants[j]; cants[j] = auxC;
                Empleado auxE = emps[i]; emps[i] = emps[j]; emps[j] = auxE;
            }
        }
    }
}
