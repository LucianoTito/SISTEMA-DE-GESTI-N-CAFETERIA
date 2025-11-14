#include<iostream>
#include <string>
#include <cstdio>
#include "../../Headers/Persistence/ArchivoPedido.h"
#include "../../Headers/Entities/Pedido.h"

using namespace std;


//Constructor

ArchivoPedido::ArchivoPedido(std::string nombreArchivo){

_nombreArchivo = nombreArchivo;

}

//Grabar registro

bool ArchivoPedido::grabarRegistro(Pedido reg){

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "ab");

if(pArchivo == nullptr){

    cout<< "Error al abrir el archivo para grabar  Pedido."<<endl;

    return false;

}

bool escribio = fwrite(&reg, sizeof(Pedido), 1, pArchivo);

fclose(pArchivo);

return escribio;



}

//Contar registros

int ArchivoPedido::contarRegistros(){


FILE *pArchivo = fopen(_nombreArchivo.c_str(),"rb");

if(pArchivo == nullptr){

    return 0;
}
fseek(pArchivo, 0L, SEEK_END);

long tamanioEnBytes = ftell(pArchivo);

    fclose(pArchivo);

    int cantidadRegistros = tamanioEnBytes /sizeof(Pedido);

    return cantidadRegistros;


}

//Leer Registro

Pedido ArchivoPedido::leerRegistro(int posicion){


Pedido reg;



FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");


if(pArchivo == nullptr) {

    return reg;
}

fseek(pArchivo, posicion *sizeof(Pedido), SEEK_SET);

fread(&reg, sizeof(Pedido), 1,pArchivo);

fclose(pArchivo);

return reg;


}

//Buscar registro

int ArchivoPedido::buscarRegistro(int idPedido){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    return -1;
}

Pedido regLeido;

int posicionActual=0;

while(fread(&regLeido, sizeof(Pedido), 1, pArchivo)==1){

    if (regLeido.getIdPedido() == idPedido){

        fclose(pArchivo);

        return posicionActual;
    }
    posicionActual++;
}

fclose(pArchivo);

return -1;

}

//Modificar registro

bool ArchivoPedido::modificarRegistro(Pedido reg, int posicion){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");

if (pArchivo == nullptr){

    cout<< "Error al abrir el archivo para modificar Pedido."<<endl;

    return false;
}

fseek(pArchivo, posicion * sizeof(Pedido), SEEK_SET);

bool escribio = fwrite(&reg, sizeof(Pedido), 1, pArchivo);

fclose(pArchivo);

return escribio;

}

//Listar

void ArchivoPedido::listar(){

    listarPorEstado(false);
}

void ArchivoPedido::listarEliminados(){

listarPorEstado(true);

}

void ArchivoPedido::listarPorEstado(bool eliminado) {

    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

    if(pArchivo == nullptr){
        cout<< "Error al abrir el archivo para listar Pedido."<<endl;
        return;
    }

    Pedido regLeido;
    bool hayPedidos = false;

    cout << endl
         << (eliminado ? "------- PEDIDOS ANULADOS -------"
                       : "------- PEDIDOS ACTIVOS -------")
         << endl;

    while(fread(&regLeido, sizeof(Pedido), 1, pArchivo)==1){

        if(regLeido.getEliminado() == eliminado){
            regLeido.Mostrar();
            hayPedidos = true;
        }
    }

    if (!hayPedidos){
        cout << (eliminado ? "No hay pedidos anulados para mostrar."
                           : "No hay pedidos activos para mostrar.")
             << endl;
    }

    cout << "------- FIN DEL LISTADO -------" << endl << endl;

    fclose(pArchivo);
}


bool ArchivoPedido::hayPedidosConEstado(bool eliminado){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){
    return false;
}

Pedido regLeido;

while (fread(&regLeido, sizeof(Pedido), 1, pArchivo) == 1){

    if(regLeido.getEliminado()== eliminado){
        fclose(pArchivo);
        return true;
    }

}

fclose(pArchivo);
return false;


}

bool ArchivoPedido::restaurarCantidadRegistros(int cantidadRegistros){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){
    return (cantidadRegistros == 0);
}

std::string nombreTemporal = _nombreArchivo + ".temp";
FILE *pTemporal = fopen(nombreTemporal.c_str(), "wb");

if(pTemporal == nullptr){
    fclose(pArchivo);
    cout << "Error al crear el archivo temporal para restaurar Pedidos"<<endl;
    return false;

}

Pedido regLeido;
int copiados = 0;

while(copiados < cantidadRegistros && fread(&regLeido, sizeof(Pedido), 1, pArchivo)==1){

    fwrite(&regLeido, sizeof(Pedido), 1, pTemporal);
    copiados++;
}

fclose(pArchivo);
fclose(pTemporal);

remove(_nombreArchivo.c_str());
rename(nombreTemporal.c_str(), _nombreArchivo.c_str());


return copiados == cantidadRegistros;


}













