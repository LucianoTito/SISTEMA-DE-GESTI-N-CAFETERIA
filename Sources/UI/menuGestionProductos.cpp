#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio> // Para sprintf
#include <iomanip>

#include "../../Headers/UI/menuGestionProductos.h"
#include "../../Headers/Entities/Producto.h"
#include "../../Headers/Persistence/ArchivoProducto.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Tablas.h"

using namespace std;

// ==========================================
// PROTOTIPOS AUXILIARES (PRIVADOS)
// ==========================================
void listarProductosGenerico(bool mostrarEliminados);
void mostrarEncabezadoProductos();
void mostrarFilaProducto(Producto p);

// Helpers de lógica
int buscarProductoID(ArchivoProducto& arc, bool buscarEliminados);
Producto* obtenerProductosActivos(int &cantidad);
void ordenarProductosPorNombre(Producto registros[], int cantidad);
void ordenarProductosPorPrecio(Producto registros[], int cantidad);


// ==========================================
// MENU PRINCIPAL
// ==========================================
void menuProductos() {
    int opcion;
    while (true) {
        limpiarConsola();
        imprimirTituloDecorado("GESTION DE PRODUCTOS", 80);
        rlutil::setColor(PaletaCafe::CREMA);
        cout << "1. AGREGAR PRODUCTO" << endl;
        cout << "2. LISTAR PRODUCTOS (ACTIVOS)" << endl;
        cout << "3. LISTAR PRODUCTOS DADOS DE BAJA" << endl;
        cout << "4. MODIFICAR PRODUCTO" << endl;
        cout << "5. ELIMINAR PRODUCTO" << endl;
        cout << "6. DAR DE ALTA PRODUCTO" << endl;
        cout << "7. LISTAR ORDENADOS POR NOMBRE" << endl;
        cout << "8. LISTAR ORDENADOS POR PRECIO" << endl;
        cout << "9. CONSULTAR PRODUCTO POR ID" << endl;
        cout << "10. CONSULTAR PRODUCTOS CON STOCK BAJO" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(80);
        rlutil::setColor(PaletaCafe::ESPUMA);
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaDoble(80);
        restaurarColor();

        opcion = ingresarEntero("SELECCIONE UNA OPCION: ");
        limpiarConsola();

        switch (opcion) {
            case 1: agregarProducto(); break;
            case 2: listarProductos(); break;
            case 3: listarProductosDadosDeBaja(); break;
            case 4: modificarProducto(); break;
            case 5: bajaProducto(); break;
            case 6: altaProducto(); break;
            case 7: listarProductosOrdenadosPorNombre(); break;
            case 8: listarProductosOrdenadosPorPrecio(); break;
            case 9: consultarProductoPorID(); break;
            case 10: consultarProductosConStockBajo(); break;
            case 0: return;
            default: imprimirMensajeError("Opcion incorrecta.");
            break;
        }
        pausarConsola();
    }
}

// ==========================================
// ABM: ALTA, BAJA, MODIFICACION
// ==========================================

void agregarProducto() {
    ArchivoProducto arcProducto("Productos.dat");
    Producto regProducto;
    int nuevoID = arcProducto.contarRegistros() + 1;

    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(80);
    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << "☕ AGREGAR NUEVO PRODUCTO" << endl;
    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(80);
    restaurarColor();


    regProducto.Cargar(nuevoID);

    if (arcProducto.grabarRegistro(regProducto)) {
            rlutil::setColor(PaletaCafe::OK);
        cout << "Producto agregado exitosamente." << endl;
    } else {
            rlutil::setColor(PaletaCafe::ERROR);
        cout << "Error: No se pudo agregar el producto." << endl;
    }
}

void modificarProducto() {
    ArchivoProducto arcProducto("Productos.dat");


       rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(80);
    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << "🍪 MODIFICAR PRODUCTO" << endl;
    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(80);
    restaurarColor();

    int pos = buscarProductoID(arcProducto, false);
    if (pos == -1) return;

    Producto reg = arcProducto.leerRegistro(pos);

    rlutil::setColor(PaletaCafe::CREMA);
    cout << endl << "Producto seleccionado:" << endl;
    mostrarEncabezadoProductos();
    mostrarFilaProducto(reg);
    lineaSimple(80);

    rlutil::setColor(PaletaCafe::CREMA);
    cout << "1) Nombre | 2) Precio | 3) Stock | 0) Cancelar" << endl;

    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(80);
    restaurarColor();
    int opc = ingresarEntero("Que desea modificar?: ");

    switch (opc) {
        case 1: {
            char nuevoNombre[50];
            cargarCadenaObligatoria("Nuevo nombre: ", "No puede ser vacio", nuevoNombre, 49);
            reg.setNombre(nuevoNombre);
            break;
        }
        case 2: {
            float precio = ingresarFloat("Nuevo precio: ");
            reg.setPrecio(precio);
            break;
        }
        case 3: {
            int stock = ingresarEntero("Nuevo stock: ");
            reg.setStock(stock);
            break;
        }
        case 0: return;
        default: cout << "Opcion invalida." << endl; return;
    }

    if (arcProducto.modificarRegistro(reg, pos)) cout << "Producto modificado." << endl;
    else cout << "Error al guardar." << endl;
}

void bajaProducto() {
    ArchivoProducto arcProducto("Productos.dat");
    cout << "-------- ELIMINAR PRODUCTO --------" << endl;

    int pos = buscarProductoID(arcProducto, false);
    if (pos == -1) return;

    Producto reg = arcProducto.leerRegistro(pos);

    cout << endl << "Va a eliminar:" << endl;
    mostrarEncabezadoProductos();
    mostrarFilaProducto(reg);

    char conf;
    cout << "Confirmar? (S/N): "; cin >> conf;
    if (conf == 'S' || conf == 's') {
        reg.setEliminado(true);
        if (arcProducto.modificarRegistro(reg, pos)) cout << "Producto eliminado." << endl;
        else cout << "Error al eliminar." << endl;
    }
}

void altaProducto() {
    ArchivoProducto arcProducto("Productos.dat");
    cout << "---------- RECUPERAR PRODUCTO ----------" << endl;

    int pos = buscarProductoID(arcProducto, true);
    if (pos == -1) return;

    Producto reg = arcProducto.leerRegistro(pos);

    cout << endl << "Va a recuperar:" << endl;
    mostrarEncabezadoProductos();
    mostrarFilaProducto(reg);

    char conf;
    cout << "Confirmar alta? (S/N): "; cin >> conf;
    if (conf == 'S' || conf == 's') {
        reg.setEliminado(false);
        if (arcProducto.modificarRegistro(reg, pos)) cout << "Producto recuperado." << endl;
        else cout << "Error al recuperar." << endl;
    }
}

// ==========================================
// LISTADOS Y CONSULTAS
// ==========================================

void listarProductos() {
    listarProductosGenerico(false);
}

void listarProductosDadosDeBaja() {
    listarProductosGenerico(true);
}

void consultarProductoPorID() {
    ArchivoProducto arc("Productos.dat");
    cout << "----- CONSULTA POR ID -----" << endl;

    int id = ingresarEntero("ID a buscar: ");
    int pos = arc.buscarRegistro(id);

    if (pos == -1) { cout << "No encontrado." << endl; return; }

    Producto p = arc.leerRegistro(pos);
    mostrarEncabezadoProductos();
    mostrarFilaProducto(p);
    lineaSimple(80);
    cout << "Estado: " << (p.getEliminado() ? "ELIMINADO" : "ACTIVO") << endl;
}

void consultarProductosConStockBajo() {
    ArchivoProducto arc("Productos.dat");
    if (!arc.hayProductosConEstadoEliminado(false)) {
        cout << "No hay productos activos." << endl; return;
    }

    int umbral = ingresarEntero("Ingrese stock minimo a controlar: ");
    if (umbral < 0) umbral = 0;

    cout << endl << "PRODUCTOS CON STOCK MENOR A " << umbral << ":" << endl;
    mostrarEncabezadoProductos();

    int total = arc.contarRegistros();
    bool hubo = false;
    for (int i = 0; i < total; i++) {
        Producto p = arc.leerRegistro(i);
        if (!p.getEliminado() && p.getStock() < umbral) {
            mostrarFilaProducto(p);
            hubo = true;
        }
    }
    lineaSimple(80);
    if (!hubo) cout << "Todos los productos tienen stock suficiente." << endl;
}

// ==========================================
// ORDENAMIENTOS
// ==========================================

void listarProductosOrdenadosPorNombre() {
    int cantidad = 0;
    Producto* vector = obtenerProductosActivos(cantidad);

    if (vector == nullptr) return;

    ordenarProductosPorNombre(vector, cantidad);

    cout << "----- ORDENADO POR NOMBRE -----" << endl;
    mostrarEncabezadoProductos();
    for (int i = 0; i < cantidad; i++) mostrarFilaProducto(vector[i]);
    lineaSimple(80);

    delete[] vector;
}

void listarProductosOrdenadosPorPrecio() {
    int cantidad = 0;
    Producto* vector = obtenerProductosActivos(cantidad);

    if (vector == nullptr) return;

    ordenarProductosPorPrecio(vector, cantidad);

    cout << "----- ORDENADO POR PRECIO -----" << endl;
    mostrarEncabezadoProductos();
    for (int i = 0; i < cantidad; i++) mostrarFilaProducto(vector[i]);
    lineaSimple(80);

    delete[] vector;
}

// ==========================================
// FUNCIONES PRIVADAS (HELPERS)
// ==========================================

void listarProductosGenerico(bool mostrarEliminados) {
    ArchivoProducto arc("Productos.dat");
    if (!arc.hayProductosConEstadoEliminado(mostrarEliminados)) {
        cout << "No hay productos " << (mostrarEliminados ? "eliminados" : "activos") << " para mostrar." << endl;
        return;
    }

    cout << "LISTADO DE PRODUCTOS " << (mostrarEliminados ? "(BAJAS)" : "(ACTIVOS)") << endl;
    mostrarEncabezadoProductos();

    int total = arc.contarRegistros();
    for (int i = 0; i < total; i++) {
        Producto p = arc.leerRegistro(i);
        if (p.getEliminado() == mostrarEliminados) {
            mostrarFilaProducto(p);
        }
    }
    lineaSimple(80);
}

int buscarProductoID(ArchivoProducto& arc, bool buscarEliminados) {
    if (!arc.hayProductosConEstadoEliminado(buscarEliminados)) {
        cout << "No hay productos " << (buscarEliminados ? "eliminados" : "activos") << " disponibles." << endl;
        return -1;
    }

    listarProductosGenerico(buscarEliminados);
    cout << endl;

    int id = ingresarEntero("Ingrese ID: ");
    int pos = arc.buscarRegistro(id);

    if (pos == -1) {
        cout << "ID no encontrado." << endl;
        return -1;
    }

    Producto p = arc.leerRegistro(pos);
    if (p.getEliminado() != buscarEliminados) {
        cout << "El producto seleccionado " << (p.getEliminado() ? "esta eliminado." : "esta activo.") << endl;
        return -1;
    }
    return pos;
}

Producto* obtenerProductosActivos(int &cantidad) {
    ArchivoProducto arc("Productos.dat");
    int total = arc.contarRegistros();

    if (total == 0 || !arc.hayProductosConEstadoEliminado(false)) {
        cout << "No hay productos para listar." << endl;
        cantidad = 0;
        return nullptr;
    }

    Producto* temp = new Producto[total];
    cantidad = 0;

    for (int i = 0; i < total; i++) {
        Producto p = arc.leerRegistro(i);
        if (!p.getEliminado()) {
            temp[cantidad] = p;
            cantidad++;
        }
    }
    return temp;
}

void mostrarEncabezadoProductos() {
    lineaDoble(80);
    // Llama a la funcion de Tablas.cpp
    imprimirFilaProducto("ID", "NOMBRE", "PRECIO ($)", "STOCK");
    lineaSimple(80); // Ajustado a 80
}

void mostrarFilaProducto(Producto p) {
    char sId[10], sPrecio[20], sStock[10];
    sprintf(sId, "%d", p.getIdProducto());
    sprintf(sPrecio, "%.2f", p.getPrecio());
    sprintf(sStock, "%d", p.getStock());

    imprimirFilaProducto(sId, p.getNombre(), sPrecio, sStock);
}

void ordenarProductosPorNombre(Producto registros[], int cantidad) {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = i + 1; j < cantidad; j++) {
            if (strcmp(registros[i].getNombre(), registros[j].getNombre()) > 0) {
                Producto aux = registros[i];
                registros[i] = registros[j];
                registros[j] = aux;
            }
        }
    }
}

void ordenarProductosPorPrecio(Producto registros[], int cantidad) {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = i + 1; j < cantidad; j++) {
            if (registros[i].getPrecio() > registros[j].getPrecio()) {
                Producto aux = registros[i];
                registros[i] = registros[j];
                registros[j] = aux;
            }
        }
    }
}
