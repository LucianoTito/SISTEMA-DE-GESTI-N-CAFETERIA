#include <iostream>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include "../../Headers/Entities/Cliente.h"

#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;

//Constructor

Cliente::Cliente(int id,
                 const char* nombre,
                 const char* apellido,
                 const char* telefono,
                 const char* mail,
                 bool eliminado)
    : Persona(id, nombre, apellido, telefono, mail, eliminado)
{

}

//Cargar()
void Cliente::Cargar(int id) {

Persona::Cargar(id);

cout <<endl;

}


//Mostrar

void Cliente::Mostrar() {
    cout << "--- DATOS DEL CLIENTE ---" << endl;

    Persona::Mostrar();
    cout << "-------------------------" << endl;
}

// Imprime una fila formateada en tabla para listados compactos.
void Cliente::MostrarFila(const char* estado){
    cout << left
         << setw(6) << _id
         << setw(15) << _nombre
         << setw(15) << _apellido
         << setw(16) << _telefono
         << setw(28) << _mail;


    // El estado es opcional para reutilizar el método en listados sin esa columna.
    if(estado != nullptr){
        cout << estado;
    }

    cout << endl;
}
