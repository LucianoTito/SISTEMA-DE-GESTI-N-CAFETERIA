#include<iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include "../../Headers/Persistence/ArchivoCliente.h"
#include "../../Headers/Entities/Cliente.h"

using namespace std;


//Constructor

ArchivoCliente::ArchivoCliente(std::string nombreArchivo){
_nombreArchivo = nombreArchivo;

}

//Grabar registro

bool ArchivoCliente::grabarRegistro (Cliente reg) {

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");

if(pArchivo == nullptr) {

    cout<< "Error al abrir el archivo para grabar Cliente"<<endl;

    return false;
}

bool escribio = fwrite(&reg, sizeof (Cliente), 1, pArchivo);

fclose(pArchivo);

return escribio;
}

//ContarRegistros

int ArchivoCliente::contarRegistros() {

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr) {

    return 0;
}

fseek(pArchivo, 0L, SEEK_END);

long tamanioEnBytes = ftell(pArchivo);

fclose (pArchivo);

int cantidadRegistros = tamanioEnBytes / sizeof (Cliente);

return cantidadRegistros;

}

//Leer registro

Cliente ArchivoCliente::leerRegistro (int posicion){

Cliente reg;

reg.setId(-1);

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");


if (pArchivo == nullptr){

    return reg;
}
fseek(pArchivo, posicion* sizeof(Cliente), SEEK_SET);

fread (&reg, sizeof(Cliente), 1 , pArchivo);

fclose(pArchivo);

return reg;

}

//Buscar registro

int ArchivoCliente::buscarRegistro(int idCliente){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){
    return -1;
}

//Creación de un obj temporal
Cliente regLeido;
int posicionActual = 0;

while (fread( &regLeido, sizeof(Cliente), 1, pArchivo) == 1){

    if(regLeido.getId() == idCliente) {

        fclose(pArchivo);

        return posicionActual;
    }
    posicionActual++;
}

fclose(pArchivo);

return -1;

}

//Modificar registro

bool ArchivoCliente::modificarRegistro(Cliente reg, int posicion ){


FILE *pArchivo = fopen (_nombreArchivo.c_str(), "rb+");

if (pArchivo == nullptr){

    cout<< "Error al abrir el archivo para modificar Cliente."<<endl;

    return false;
}

fseek(pArchivo, posicion * sizeof (Cliente), SEEK_SET);

bool escribio = fwrite(&reg, sizeof(Cliente),1 , pArchivo);

fclose (pArchivo);

return escribio;


}


//Listar

void ArchivoCliente::listar() {

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){

    cout << "Error al abrir el archivo para listar a Cliente."<<endl;

    return;
}

Cliente regLeido;
bool hayClientes = false;

cout<< endl<< "------- CLIENTES ACTIVOS -------"<<endl;

while (fread (&regLeido, sizeof(Cliente), 1, pArchivo) == 1){

    if (regLeido.getEliminado()== false){

        regLeido.Mostrar();
        hayClientes = true;
    }

}
if (!hayClientes){

    cout << "No hay clientes activos para mostrar."<<endl;
}

cout <<"---------- FIN DEL LISTADO ----------" <<endl<<endl;

fclose(pArchivo);

}

void ArchivoCliente::listarEliminados(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){
    cout << "Error al abrir el archivo para listar a Clientes."<<endl;
    return;
}

Cliente regLeido;
bool hayClientes = false;

cout<< endl<< "------- CLIENTES DADOS DE BAJA -------"<<endl;

while(fread(&regLeido, sizeof(Cliente), 1, pArchivo)==1){

    if(regLeido.getEliminado()==true){
        regLeido.Mostrar();
        hayClientes=true;
    }
}

if(!hayClientes){
    cout << "No hay clientes dados de baja."<<endl;
}

cout << "------- FIN DEL LISTADO -------"<<endl<<endl;


fclose(pArchivo);
}

bool ArchivoCliente::hayClientesConEstadoEliminado(bool eliminado){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){
    return false;
}

Cliente regLeido;

while(fread(&regLeido, sizeof(Cliente), 1, pArchivo) == 1){

    if (regLeido.getEliminado() == eliminado){
        fclose(pArchivo);
        return true;
    }
}
fclose(pArchivo);

return false;

}

void ArchivoCliente::listarOrdenadosPorApellido(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){
    cout << "Error al abrir el archivo para listar Clientes."<<endl;
    return;
}

Cliente regLeido;
int cantidadActivos = 0;

while(fread(&regLeido, sizeof(Cliente), 1, pArchivo) == 1){
    if(regLeido.getEliminado()==false){
        cantidadActivos++;
    }
}

if(cantidadActivos == 0){
    cout << "No hay clientes activos para listar por apellido."<<endl;
    fclose(pArchivo);
    return;
}

Cliente *clientes = new Cliente[cantidadActivos];
rewind(pArchivo);
int indice = 0;

while(fread(&regLeido, sizeof(Cliente), 1, pArchivo) == 1){
    if(regLeido.getEliminado()==false){
        clientes[indice] = regLeido;
        indice++;
    }
}

fclose(pArchivo);

for(int i = 0; i < cantidadActivos - 1; i++){
    for(int j = 0; j < cantidadActivos - 1 - i; j++){
        int comparacion = strcmp(clientes[j].getApellido(), clientes[j+1].getApellido());
        if(comparacion > 0 || (comparacion == 0 && strcmp(clientes[j].getNombre(), clientes[j+1].getNombre()) > 0)){
            Cliente aux = clientes[j];
            clientes[j] = clientes[j+1];
            clientes[j+1] = aux;
        }
    }
}

cout << endl << "------- CLIENTES ORDENADOS POR APELLIDO -------"<<endl;
for(int i = 0; i < cantidadActivos; i++){
    clientes[i].Mostrar();
}
cout << "----------------------------------------"<<endl<<endl;

delete [] clientes;

}

void ArchivoCliente::listarOrdenadosPorPuntosDeFidelidad(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){
    cout << "Error al abrir el archivo para listar Clientes."<<endl;
    return;
}

Cliente regLeido;
int cantidadActivos = 0;

while(fread(&regLeido, sizeof(Cliente), 1, pArchivo) == 1){
    if(regLeido.getEliminado()==false){
        cantidadActivos++;
    }
}

if(cantidadActivos == 0){
    cout << "No hay clientes activos para listar por puntos de fidelidad."<<endl;
    fclose(pArchivo);
    return;
}

Cliente *clientes = new Cliente[cantidadActivos];
rewind(pArchivo);
int indice = 0;

while(fread(&regLeido, sizeof(Cliente), 1, pArchivo) == 1){
    if(regLeido.getEliminado()==false){
        clientes[indice] = regLeido;
        indice++;
    }
}

fclose(pArchivo);

for(int i = 0; i < cantidadActivos - 1; i++){
    for(int j = 0; j < cantidadActivos - 1 - i; j++){
        if(clientes[j].getPuntosFidelidad() < clientes[j+1].getPuntosFidelidad()){
            Cliente aux = clientes[j];
            clientes[j] = clientes[j+1];
            clientes[j+1] = aux;
        }
        else if(clientes[j].getPuntosFidelidad() == clientes[j+1].getPuntosFidelidad()){
            int comparacionApellido = strcmp(clientes[j].getApellido(), clientes[j+1].getApellido());
            if(comparacionApellido > 0 || (comparacionApellido == 0 && strcmp(clientes[j].getNombre(), clientes[j+1].getNombre()) > 0)){
                Cliente aux = clientes[j];
                clientes[j] = clientes[j+1];
                clientes[j+1] = aux;
            }
        }
    }
}

cout << endl << "--- CLIENTES ORDENADOS POR PUNTOS DE FIDELIDAD ---"<<endl;
for(int i = 0; i < cantidadActivos; i++){
    clientes[i].Mostrar();
}
cout << "-------------------------------------------------"<<endl<<endl;

delete [] clientes;

}







