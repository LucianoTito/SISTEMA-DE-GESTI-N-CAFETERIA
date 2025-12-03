#include <iostream>
#include <cstring>
#include <iomanip>

#include <cstdio>  // Necesaria para fflush

#include "../../Headers/Entities/Producto.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Tablas.h"



using namespace std;


Producto::Producto(int idProducto,
                   const char* nombre,
                   float precio,
                   int stock,
                   bool eliminado) {
    setIdProducto(idProducto);
    setNombre(nombre);
    setPrecio(precio);
    setStock(stock);
    setEliminado(eliminado);
}

//Getters
int Producto::getIdProducto() { return _idProducto; }
const char* Producto::getNombre() { return _nombre; }
float Producto::getPrecio() { return _precio; }
int Producto::getStock() { return _stock; }
bool Producto::getEliminado() { return _eliminado; }


//Setters
void Producto::setIdProducto(int idProducto) {
    if (idProducto >= 0) {
        _idProducto = idProducto;
    } else {
        cout << "ID incorrecto. Debe ser igual o mayor a 0. Se asignara 0 por defecto." << endl;
        _idProducto = 0;
    }
}

void Producto::setNombre(const char* nombre) {
     if (nombre != nullptr && nombre[0] != '\0') {
         if (strlen(nombre) < 50) {
            strcpy(_nombre, nombre);
         } else {
            cout << "Nombre demasiado largo. Se cortará en 49 caracteres." << endl;
            strncpy(_nombre, nombre, 49);
            _nombre[49] = '\0';
         }
     } else {
        cout << "Nombre invalido. Se asignara 'Sin Nombre'." << endl;
        strcpy(_nombre, "Sin Nombre");
     }
}

void Producto::setPrecio(float precio) {
    if (precio >= 0.0f) {
        _precio = precio;
    } else {
        cout << "Precio invalido. No puede ser negativo. Se asignara 0.0." << endl;
        _precio = 0.0f;
    }
}

void Producto::setStock(int stock) {
    if (stock >= 0) {
        _stock = stock;
    } else {
        cout << "Stock invalido. No puede ser negativo. Se asignara 0." << endl;
        _stock = 0;
    }
}

void Producto::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}

//Métodos Cargar() y Mostrar()

void Producto::Cargar(int idProducto) {



    setIdProducto(idProducto);
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(60);
    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << "🍮 NUEVO PRODUCTO" << endl;
    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(60);
    restaurarColor();

    rlutil::setColor(PaletaCafe::CREMA);
    cout << "ID asignado: ";
    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << idProducto << endl;

    char nombre[50]; // Variable temporal para el nombre
    imprimirPrompt("Ingrese Nombre: ");
    rlutil::setColor(PaletaCafe::ESPUMA);
    cargarCadena(nombre, 49);
    setNombre(nombre); //setter para asignar y validar longitud

    //Valido precio
        rlutil::setColor(PaletaCafe::ESPUMA);
    float precio = ingresarFloat("Ingrese Precio: ");
    setPrecio(precio);


    //valido stock
    rlutil::setColor(PaletaCafe::ESPUMA);
    int stock = ingresarEntero("Ingrese Stock: ");
    setStock(stock);


    _eliminado = false; // Un producto nuevo siempre inicia activo
    rlutil::setColor(PaletaCafe::OK);
    cout << "Producto cargado correctamente." << endl;
    restaurarColor();
}

void Producto::Mostrar() {
    cout << "-----------------------------" << endl;
    cout << "ID Producto: " << _idProducto << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Precio: $" << _precio << endl;
    cout << "Stock: " << _stock << endl;
    cout << "-----------------------------" << endl;
}

void Producto::MostrarFila(const char* estado){
//Muestra los estado en formato de tabla para evitar listado muy extensos hacia abajo.
cout<< left
<< setw(6) << _idProducto
<< setw(30) <<_nombre
<< "$" << setw(10) << fixed << setprecision(2) << _precio
<< setw(8) << _stock;

// El estado es opcional porque en algunos listados solo se muestran activos.
if (estado != nullptr){
    cout << estado;
}

cout << endl;
}
