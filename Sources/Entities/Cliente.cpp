#include <iostream>
#include <cstring>
#include <cstdio>
//#include "Cliente.h"
#include "../../Headers/Entities/Cliente.h"

#include "../../Headers/Utilidades/Validaciones.h"




using namespace std;

//Constructor

Cliente::Cliente(int id,
                 const char* nombre,
                 const char* apellido,
                 bool eliminado,
                 const char* telefono,
                 int puntosFidelidad)
    : Persona(id, nombre, apellido, eliminado)
{
    setTelefono(telefono);
    setPuntosFidelidad(puntosFidelidad);
}

//Getters ESPECÍFICOS de Cliente


const char* Cliente::getTelefono() {
    return _telefono;
}

int Cliente::getPuntosFidelidad() {
    return _puntosFidelidad;
}

// --- Setters ESPECÍFICOS de Cliente ---

void Cliente::setTelefono(const char* telefono) {

    if (telefono != nullptr && telefono[0] != '\0') {
        if (strlen(telefono) < 20) {
            strcpy(_telefono, telefono);
        } else {
            cout << "Telefono demasiado largo. Se cortara en 19 caracteres." << endl;
            strncpy(_telefono, telefono, 19);
            _telefono[19] = '\0';
        }
    } else {
        cout << "Telefono invalido. Se asignara 'Sin numero'." << endl;
        strcpy(_telefono, "Sin numero");
    }
}

void Cliente::setPuntosFidelidad(int puntos) {

    if (puntos >= 0) {
        _puntosFidelidad = puntos;
    } else {
        cout << "Puntos de fidelidad invalidos. No pueden ser negativos. Se asignara 0." << endl;
        _puntosFidelidad = 0;
    }
}

//Cargar()
void Cliente::Cargar(int id) {

char telefono[20];

Persona::Cargar(id);

cout << "Ingrese el numero de telefono: "<<endl;
cargarCadena(telefono, 20);
setTelefono(telefono); //setter para asignar y validar longitud

cout <<endl;
int puntaje = ingresarEntero("Por favor ingrese el puntaje de fidelidad: ");
setPuntosFidelidad(puntaje);
}


//Mostrar

void Cliente::Mostrar() {
    cout << "--- DATOS DEL CLIENTE ---" << endl;

    Persona::Mostrar();

    cout << "Telefono: " << _telefono << endl;
    cout << "Puntos Fidelidad: " << _puntosFidelidad << endl;
    cout << "-------------------------" << endl;
}
