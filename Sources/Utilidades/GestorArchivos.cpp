#include <iostream>
#include <cstdio>
#include <cstring>

#include "../../Headers/Utilidades/GestorArchivos.h"
#include "../../Headers/Entities/Cliente.h"
#include "../../Headers/Entities/Producto.h"
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/Entities/Pedido.h"
#include "../../Headers/Entities/DetallePedido.h"
#include "../../Headers/Entities/Pagos.h"
#include "../../Headers/Entities/Fecha.h"

using namespace std;

// Verifica si un archivo existe intentando abrirlo en modo lectura binaria.
bool existeArchivo(const char* nombreArchivo) {
    FILE* p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return false;
    fclose(p);
    return true;
}

/**
 * Copia un archivo binario de origen a destino.
 * Utiliza un BUFFER de memoria para no leer byte por byte, lo que hace
 * que la copia sea muchisimo mas rapida y eficiente.
 */
bool copiarArchivoBinario(const char* origen, const char* destino) {
    FILE* in = fopen(origen, "rb");
    if (in == nullptr) {
        cout << "ERROR: No se pudo abrir el archivo de origen: " << origen << endl;
        return false;
    }
    FILE* out = fopen(destino, "wb");
    if (out == nullptr) {
        cout << "ERROR: No se pudo crear el archivo de destino: " << destino << endl;
        fclose(in);
        return false;
    }

    // Buffer de 4KB: Leemos bloques grandes en lugar de 1 byte a la vez
    const int BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];
    size_t bytesLeidos;

    // Bucle de copia: Lee un bloque -> Escribe el bloque
    while ((bytesLeidos = fread(buffer, 1, BUFFER_SIZE, in)) > 0) {
        fwrite(buffer, 1, bytesLeidos, out);
    }

    fclose(in);
    fclose(out);
    return true;
}

// --- IMPLEMENTACION DE EXPORTACIONES A CSV ---
// Todas las funciones siguen el mismo patron:
// 1. Abrir archivo .dat (origen)
// 2. Crear archivo .csv (destino)
// 3. Escribir cabecera de columnas
// 4. Recorrer registro por registro y escribirlo separado por comas

bool exportarClientesCSV(const char* csvDestino) {
    FILE* pDat = fopen("Clientes.dat", "rb");
    if (pDat == nullptr) return false;

    FILE* pCsv = fopen(csvDestino, "w");
    if (pCsv == nullptr) { fclose(pDat); return false; }

    // Cabecera del Excel/CSV
    fprintf(pCsv, "ID,Nombre,Apellido,Telefono,Mail,Eliminado\n");

    Cliente reg;
    // Lectura secuencial
    while(fread(&reg, sizeof(Cliente), 1, pDat) == 1){
        fprintf(pCsv, "%d,%s,%s,%s,%s,%d\n",
                reg.getId(), reg.getNombre(), reg.getApellido(),
                reg.getTelefono(), reg.getMail(), reg.getEliminado());
    }

    fclose(pDat);
    fclose(pCsv);
    return true;
}

bool exportarProductosCSV(const char* csvDestino) {
    FILE* pDat = fopen("Productos.dat", "rb");
    if (pDat == nullptr) return false;

    FILE* pCsv = fopen(csvDestino, "w");
    if (pCsv == nullptr) { fclose(pDat); return false; }

    fprintf(pCsv, "ID,Nombre,Precio,Stock,Eliminado\n");

    Producto reg;
    while(fread(&reg, sizeof(Producto), 1, pDat) == 1){
        // %.2f formatea el float a 2 decimales para el precio
        fprintf(pCsv, "%d,%s,%.2f,%d,%d\n",
                reg.getIdProducto(), reg.getNombre(), reg.getPrecio(),
                reg.getStock(), reg.getEliminado());
    }

    fclose(pDat);
    fclose(pCsv);
    return true;
}

bool exportarEmpleadosCSV(const char* csvDestino) {
    FILE* pDat = fopen("Empleados.dat", "rb");
    if (pDat == nullptr) return false;

    FILE* pCsv = fopen(csvDestino, "w");
    if (pCsv == nullptr) { fclose(pDat); return false; }

    fprintf(pCsv, "ID,Nombre,Apellido,Puesto,Eliminado\n");

    Empleado reg;
    while(fread(&reg, sizeof(Empleado), 1, pDat) == 1){
        fprintf(pCsv, "%d,%s,%s,%s,%d\n",
                reg.getId(), reg.getNombre(), reg.getApellido(),
                reg.getPuesto(), reg.getEliminado());
    }

    fclose(pDat);
    fclose(pCsv);
    return true;
}

bool exportarPedidosCSV(const char* csvDestino) {
    FILE* pDat = fopen("Pedidos.dat", "rb");
    if (pDat == nullptr) return false;

    FILE* pCsv = fopen(csvDestino, "w");
    if (pCsv == nullptr) { fclose(pDat); return false; }

    fprintf(pCsv, "ID_Pedido,ID_Cliente,ID_Empleado,Nro_Mesa,Fecha,Subtotal,Descuento,Eliminado\n");

    Pedido reg;
    while(fread(&reg, sizeof(Pedido), 1, pDat) == 1){
        Fecha f = reg.getFecha();
        // Formateamos la fecha como DD/MM/AAAA en una sola columna
        fprintf(pCsv, "%d,%d,%d,%d,%d/%d/%d,%.2f,%d,%d\n",
                reg.getIdPedido(), reg.getIdCliente(), reg.getIdEmpleado(),
                reg.getNroMesa(), f.getDia(), f.getMes(), f.getAnio(),
                reg.getSubtotal(), reg.getPorcentajeDescuento(), reg.getEliminado());
    }

    fclose(pDat);
    fclose(pCsv);
    return true;
}

bool exportarDetallesCSV(const char* csvDestino) {
    FILE* pDat = fopen("DetallesPedidos.dat", "rb");
    if (pDat == nullptr) return false;

    FILE* pCsv = fopen(csvDestino, "w");
    if (pCsv == nullptr) { fclose(pDat); return false; }

    fprintf(pCsv, "ID_Detalle,ID_Pedido,ID_Producto,Cantidad,Precio_Unitario,Subtotal\n");

    DetallePedido reg;
    while(fread(&reg, sizeof(DetallePedido), 1, pDat) == 1){
        // Calculamos el subtotal al vuelo para exportarlo
        float subtotal = reg.getCantidad() * reg.getPrecioUnitario();
        fprintf(pCsv, "%d,%d,%d,%d,%.2f,%.2f\n",
                reg.getIdDetalle(), reg.getIdPedido(), reg.getIdProducto(),
                reg.getCantidad(), reg.getPrecioUnitario(), subtotal);
    }

    fclose(pDat);
    fclose(pCsv);
    return true;
}

bool exportarPagosCSV(const char* csvDestino) {
    FILE* pDat = fopen("Pagos.dat", "rb");
    if (pDat == nullptr) return false;

    FILE* pCsv = fopen(csvDestino, "w");
    if (pCsv == nullptr) { fclose(pDat); return false; }

    fprintf(pCsv, "ID_Pago,ID_Pedido,Fecha,Metodo,Monto\n");

    Pagos reg;
    while(fread(&reg, sizeof(Pagos), 1, pDat) == 1){
        Fecha f = reg.getFechaPago();

        // Traducimos el código numérico del método de pago a texto
        const char* metodo = (reg.getMetodoPago() == 1) ? "Efectivo" :
                             (reg.getMetodoPago() == 2) ? "Tarjeta" : "Transferencia";

        fprintf(pCsv, "%d,%d,%d/%d/%d,%s,%.2f\n",
                reg.getIdPago(), reg.getIdPedido(),
                f.getDia(), f.getMes(), f.getAnio(),
                metodo, reg.getMontoPagado());
    }

    fclose(pDat);
    fclose(pCsv);
    return true;
}
