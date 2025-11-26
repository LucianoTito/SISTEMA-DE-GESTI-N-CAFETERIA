#include<iostream>
#include <string>
#include <cstdio>
#include <iomanip>

#include "../../Headers/Persistence/ArchivoProducto.h"
#include "../../Headers/Entities/Producto.h"

using namespace std;

//Constantes de filtro para listado en tabla.
//1 = Solo activos, 2 = Solo dados de baja, 3 = Todos

const int FILTRO_ACTIVOS = 1;
const int FILTRO_ELIMINADOS = 2;
const int FILTRO_TODOS = 3;

//Encabezado común para evitar que el listado sea muy largo verticalmente.
void mostrarEncabezadoTablaProductos(bool incluirEstado){

cout << left
     << setw(6) << "ID"
     << setw(32) << "Nombre"
     << setw(12) << "Precio"
     << setw(8) << "Stock";

     if(incluirEstado){
        cout << "Estado";
     }

     cout << endl;
// Dibuja una línea de separación debajo del encabezado.
// Si se incluye la columna Estado, la tabla es más ancha (70 guiones).
// Si NO se incluye, la tabla es más corta (58 guiones).
     cout << string (incluirEstado ? 68 : 56, '-') <<endl; // operador ternario → elige 63 o 51


}

//Constructor

ArchivoProducto::ArchivoProducto(std::string nombreArchivo){

_nombreArchivo = nombreArchivo;

}

//Método grabarRegistro
bool ArchivoProducto::grabarRegistro (Producto reg){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");

if (pArchivo == nullptr) {

    std::cout<< "Error al abrir el archivo para grabar."<<std::endl;
    return false;

}
//Escribir registro

bool escribio = fwrite(&reg, sizeof(Producto), 1, pArchivo );

//Cerrar el archivo

fclose(pArchivo);

return escribio;

}

//Método contar registros

int ArchivoProducto::contarRegistros(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){
    return 0;
}

fseek(pArchivo, 0L, SEEK_END);

// 5. Obtener la posición actual (tamaño total)
long tamanioEnBytes = ftell(pArchivo);

fclose(pArchivo);

int cantidadRegistros = tamanioEnBytes/sizeof (Producto); //calcula la cantidad de registros

return cantidadRegistros;

}

//Método Leer Registro
Producto ArchivoProducto::leerRegistro(int posicion) {

//Se crea un objeto Producto para devolver:
Producto reg;

//se lo inicializa
reg.setIdProducto(0);


FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){

    cout << "Error al abrir el archivo para leer."<<endl;
    return reg;
}
//posicion * sizeof(Producto): Calculamos cuántos bytes saltar. Si posicion=0, saltamos 0 bytes. Si posicion=1, saltamos el tamaño de UN producto
fseek(pArchivo, posicion * sizeof(Producto), SEEK_SET);

//fread devuelve la cantidad de registros leídos (1 si tuvo éxito, 0 si no).
fread(&reg, sizeof(Producto), 1, pArchivo);

fclose(pArchivo);

return reg;

}

//Método Buscar Registro


int ArchivoProducto::buscarRegistro(int idProductoBuscado) {

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr) {

    cout<< "Error al abrir el archivo para buscar. "<<endl;
    return -1;
}

Producto regLeido; //Un obj Producto p/guardar cada registro que se lea
int posicionActual = 0; // Un contador p/saber en que posición estamos.


while(fread(&regLeido, sizeof(Producto),1, pArchivo) == 1 ){

        if(regLeido.getIdProducto()== idProductoBuscado) {

            fclose(pArchivo);
            return posicionActual;
        }
        posicionActual++; // Si no es el ID buscado, incrementamos el contador de posición para el próximo registro.

}
fclose(pArchivo);

return -1;

}


//Método modificar registro
//(permite sobreescribir un registro existente en el archivo)
//Se usa para la baja lógica y para modificar los datos de un producto (ejemplo stock)

bool ArchivoProducto::modificarRegistro(Producto reg, int posicion) {

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");

if (pArchivo == nullptr){
    cout << "Error al abrir el archivo para modificar. "<<endl;
    return false;
}

fseek(pArchivo, posicion * sizeof(Producto), SEEK_SET);

bool escribio = fwrite(&reg, sizeof(Producto), 1, pArchivo);

fclose(pArchivo);

return escribio;

}

//Método Listar

//Recorre todo el archivo y muestra por pantalla todos los productos que no estén marcados como eliminados.

void ArchivoProducto::listar(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){
    cout << "Error al abrir el archivo para listar."<<endl;
    return;
}

Producto regLeido; //Objeto p/ guardar cada producto leído.
bool hayProductos = false;

cout <<endl << "-- PRODUCTOS ACTIVOS --"<<endl;
mostrarEncabezadoTablaProductos(false);

while (fread (&regLeido, sizeof(Producto), 1, pArchivo) == 1){

   //Verificamos que el producto leído NO esté eliminado.
   if (regLeido.getEliminado() == false) {

    regLeido.MostrarFila();
    hayProductos = true;
   }
   //Si está eliminado lo ignoramos y el bucle continuá
}

if(!hayProductos){

cout<< "No hay productos activos para mostrar."<<endl;
}

cout << "------------------ FIN DEL LISTADO -----------------"<<endl;



fclose(pArchivo);
}

void ArchivoProducto::listarEliminados(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    cout << "Error al abrir el archivo para listar."<<endl;
    return;

}

Producto regLeido;
bool hayProductos = false;

cout <<endl << "-- PRODUCTOS DADOS DE BAJA --"<<endl;
mostrarEncabezadoTablaProductos(false);

while(fread(&regLeido, sizeof(Producto), 1, pArchivo)== 1) {

    if(regLeido.getEliminado() == true){
        regLeido.MostrarFila();
        hayProductos = true;
    }

}

if (!hayProductos){

    cout << "No hay productos dados de baja."<<endl;
}
cout << "--- FIN DEL LISTADO ---"<<endl;

fclose(pArchivo);

}

void ArchivoProducto::listarConFiltro (int filtroEstado){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    cout << "Error al abrir el archivo para listar."<<endl;
    return;
}

Producto regLeido;
bool hayProductos = false;

cout << "-- LISTADO DE PRODUCTOS --"<<endl;
mostrarEncabezadoTablaProductos(true);

while(fread(&regLeido, sizeof(Producto), 1, pArchivo) == 1){

    bool esEliminado = regLeido.getEliminado();

    bool cumpleFiltro = (filtroEstado == FILTRO_TODOS) ||
                         ( filtroEstado == FILTRO_ACTIVOS && !esEliminado) ||
                         (filtroEstado == FILTRO_ELIMINADOS && esEliminado);

    if(cumpleFiltro){
        const char* estado = esEliminado ? "INACTIVO" : "ACTIVO";
        regLeido.MostrarFila(estado);
        hayProductos = true;
    }
}

if(!hayProductos){
    cout << "No hay productos para mostrar con el filtro seleccionado."<<endl;
}

cout << "--------------------- FIN DEL LISTADO -----------------------"<<endl;

fclose(pArchivo);

}

bool ArchivoProducto::hayProductosConEstadoEliminado(bool eliminado){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    return false;
}

Producto regLeido;

while(fread(&regLeido, sizeof(Producto), 1, pArchivo)== 1) {


 if(regLeido.getEliminado() == eliminado ){
    fclose(pArchivo);
    return true;
}

}

fclose(pArchivo);

return false;

}


int ArchivoProducto::leerRegistros(Producto registros[], int cantidadMaxima){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    return 0;
}

int cantidadLeida = 0;

while(cantidadLeida < cantidadMaxima &&
      fread(&registros[cantidadLeida], sizeof(Producto), 1, pArchivo) == 1){

    cantidadLeida++;
}

fclose(pArchivo);

return cantidadLeida;
}

