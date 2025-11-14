#include<iostream>
#include <string>
#include <cstdio>
#include "../../Headers/Persistence/ArchivoDetallePedido.h"
#include "../../Headers/Entities/DetallePedido.h"



using namespace std;

//Constructor

ArchivoDetallePedido::ArchivoDetallePedido(std::string nombreArchivo){

_nombreArchivo = nombreArchivo;

}

//Grabar registro

bool ArchivoDetallePedido::grabarRegistro(DetallePedido reg){

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "ab");

if (pArchivo == nullptr){

    cout<< "Error al abrir el archivo para grabar DetallePedido."<<endl;

    return false;
}

bool escribio = fwrite (&reg, sizeof(DetallePedido), 1, pArchivo);

fclose(pArchivo);

return escribio;


}

//Contar Registros

int ArchivoDetallePedido::contarRegistros(){

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "rb");


if(pArchivo == nullptr){

    return 0;
}

fseek(pArchivo, 0L, SEEK_END);

long tamanioEnBytes = ftell(pArchivo);

fclose(pArchivo);

int cantidadRegistros = tamanioEnBytes/sizeof(DetallePedido);

return cantidadRegistros;

}

//Leer registro

DetallePedido ArchivoDetallePedido::leerRegistro(int posicion){

DetallePedido reg;

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){

    return reg;
}

fseek(pArchivo, posicion * sizeof(DetallePedido), SEEK_SET);

fread(&reg, sizeof(DetallePedido), 1, pArchivo);

fclose(pArchivo);

return reg;



}


//Buscar registro

int ArchivoDetallePedido::buscarRegistro(int idDetallePedido){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo==nullptr){

    return -1;
}

DetallePedido regLeido;
int posicionActual = 0;


while (fread(&regLeido, sizeof (DetallePedido), 1,pArchivo)== 1){

    if (regLeido.getIdDetalle() == idDetallePedido){

        fclose(pArchivo);

        return posicionActual;
    }
    posicionActual++;
}

fclose(pArchivo);

return -1;

}

int ArchivoDetallePedido::buscarDetallePorPedidoYProducto(int idPedido, int idProducto){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    cout<< "No hay registros para buscar detalle por pedido y producto"<<endl;
    cout<<endl;
    return -1;
}

DetallePedido regLeido;
int posicionActual = 0;

//Recorro el archivo para detectar si el producto ya está cargado en este pedido
while(fread(&regLeido, sizeof(DetallePedido),1 ,pArchivo) == 1){

    if(regLeido.getIdPedido()== idPedido && regLeido.getIdProducto() == idProducto){

        fclose(pArchivo);
        return posicionActual;
    }
    posicionActual ++;
}

fclose(pArchivo);
return -1;


}


//Modificar registro
bool ArchivoDetallePedido::modificarRegistro(DetallePedido reg, int posicion){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");

if(pArchivo == nullptr){

    cout << "Error al abrir el archivo para modificar DetallePedido."<<endl;

    return false;
}

fseek(pArchivo, posicion * sizeof(DetallePedido),SEEK_SET);

bool escribio = fwrite(&reg, sizeof(DetallePedido),1 ,pArchivo);

fclose(pArchivo);

return escribio;


}
bool ArchivoDetallePedido::restaurarCantidadRegistros(int cantidadRegistros){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){
    //Si no existe el archivo y se desea restaurar a 0 registros, se considera exitoso
    return (cantidadRegistros == 0);
}

std::string nombreTemporal = _nombreArchivo + ".temp";
FILE *pTemporal = fopen(nombreTemporal.c_str(), "wb");

if(pTemporal == nullptr){

    fclose(pArchivo);
    cout<< "Error al crear el archivo temporal para restaurar DetallePedido."<<endl;
    cout<<endl;
    return false;
}

DetallePedido regLeido;
int copiados = 0;

//Copio unicamente la cantidad deseada de registros para descartar los últimos
while (copiados < cantidadRegistros && fread(&regLeido, sizeof(DetallePedido), 1, pArchivo)==1){

    fwrite(&regLeido, sizeof(DetallePedido), 1,pTemporal);
    copiados ++;
}
fclose(pArchivo);
fclose(pTemporal);

remove(_nombreArchivo.c_str());
rename(nombreTemporal.c_str(), _nombreArchivo.c_str());

return copiados == cantidadRegistros;


}



//Listar

void ArchivoDetallePedido::listar(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){

    cout << "Error al abrir archivo para listar a DetallePedido."<<endl;
    return;
}

DetallePedido regLeido;

cout<<endl<< "---------- LISTADO DE DETALLES PEDIDOS ----------"<<endl;

while(fread(&regLeido, sizeof(DetallePedido), 1, pArchivo)==1){



        regLeido.Mostrar();

}

cout << "---------- FIN DEL LISTADO ----------"<<endl;

fclose(pArchivo);


}
