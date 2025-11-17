#include<iostream>
#include <string>
#include <cstdio>
#include "../../Headers/Persistence/ArchivoEmpleado.h"
#include "../../Headers/Entities/Empleado.h"


using namespace std;


//Constructor

ArchivoEmpleado::ArchivoEmpleado(std::string nombreArchivo){

_nombreArchivo = nombreArchivo;

}
//Grabar Registro

bool ArchivoEmpleado::grabarRegistro(Empleado reg){

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "ab");

if (pArchivo == nullptr){

    cout<< "Error al abrir el archivo para grabar Empleado."<<endl;
    return false;

}

bool escribio = fwrite(&reg, sizeof(Empleado), 1, pArchivo);

fclose(pArchivo);

return escribio;


}

//Contar registros

int ArchivoEmpleado::contarRegistros(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr) {

    return 0;
}

fseek (pArchivo, 0L, SEEK_END);

long tamanioEnBytes = ftell (pArchivo);

fclose(pArchivo);

int cantidadRegistros = tamanioEnBytes/sizeof (Empleado);

return cantidadRegistros;


}

//Leer registros

Empleado ArchivoEmpleado::leerRegistro(int posicion) {

Empleado reg;

reg.setId(0);

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    return reg;
}

fseek(pArchivo, posicion*sizeof(Empleado), SEEK_SET);

fread(&reg, sizeof (Empleado), 1, pArchivo);

fclose(pArchivo);

return reg;

}

//Buscar registro

int ArchivoEmpleado::buscarRegistro( int idEmpleado){

FILE *pArchivo  = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    return -1;
}

Empleado regLeido;
int posicionActual = 0;

while (fread (&regLeido, sizeof(Empleado), 1, pArchivo)==1){

    if(regLeido.getId()==idEmpleado){

        fclose(pArchivo);

        return posicionActual;
    }
    posicionActual++;
}

fclose(pArchivo);

return -1;

}

//Modificar registro

bool ArchivoEmpleado::modificarRegistro(Empleado reg, int posicion){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");

if(pArchivo == nullptr){

    cout<< "Error al abrir el archivo para modificar Empleado."<<endl;

    return false;
}

fseek(pArchivo, posicion*sizeof(Empleado), SEEK_SET);

bool escribio = fwrite(&reg, sizeof(Empleado), 1, pArchivo);

fclose (pArchivo);

return escribio;

}

//Listar

void ArchivoEmpleado::listar(){

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    cout<< "Error al abrir el archivo para listar Empleado."<<endl;

    return;
}
Empleado regLeido;
bool hayEmpleados = false;

cout<<endl<< "------- EMPLEADOS ACTIVOS -------"<<endl;

while(fread(&regLeido, sizeof(Empleado),1, pArchivo)==1){

    if(regLeido.getEliminado()== false){

        regLeido.Mostrar();
        hayEmpleados=true;
    }
}

if(!hayEmpleados){
    cout << "No hay empleados activos para mostrar."<<endl;
}


cout<< "---------- FIN DEL LISTADO ----------"<<endl<<endl;

fclose(pArchivo);

}

void ArchivoEmpleado::listarEliminados(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo==nullptr){

    cout << "Error al abrir el archivo para listar Empleado."<<endl;

    return;
}

Empleado regLeido;
bool hayEmpleados = false;

cout<<endl<< "---- EMPLEADOS DADOS DE BAJA ----"<<endl;

while(fread(&regLeido, sizeof(Empleado), 1, pArchivo)==1){

    if(regLeido.getEliminado()== true){

        regLeido.Mostrar();
        hayEmpleados = true;
    }
}

if(!hayEmpleados){
    cout << "No hay empleados dados de baja"<<endl;
}

cout << "---- FIN DEL LISTADO ----"<<endl<<endl;

fclose(pArchivo);


}

//Verifico si existan empleados activos/inactivos
bool ArchivoEmpleado::hayEmpleadosConEstadoEliminado(bool eliminado){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    return false;
}

Empleado regLeido;

while(fread(&regLeido,sizeof(Empleado), 1, pArchivo) == 1){

    if(regLeido.getEliminado() == eliminado){

        fclose(pArchivo);
        return true;
    }
}

fclose(pArchivo);
return false;

}

int ArchivoEmpleado::leerRegistros(Empleado registros[], int cantidadMaxima){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){
    return 0;
}

int cantidadLeida = 0;

while(cantidadLeida < cantidadMaxima &&
      fread(&registros[cantidadLeida], sizeof(Empleado), 1, pArchivo) == 1){

    cantidadLeida++;
}

fclose(pArchivo);

return cantidadLeida;

}
