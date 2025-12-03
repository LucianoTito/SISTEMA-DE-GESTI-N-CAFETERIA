#include <iostream>
#include <cstring>
#include <cstdio>

#include "../../Headers/Entities/Persona.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Tablas.h"


using namespace std;

// Constructor
Persona::Persona(int id,
                 const char* nombre,
                 const char* apellido,
                 const char* telefono,
                 const char* mail,
                 bool eliminado) {
    setId(id);
    setNombre(nombre);
    setApellido(apellido);
    setTelefono(telefono);
    setMail(mail);
    setEliminado(eliminado);
}

// Getters
int Persona::getId() { return _id; }
const char* Persona::getNombre() { return _nombre; }
const char* Persona::getApellido() { return _apellido; }
const char* Persona::getTelefono(){ return _telefono; }
const char* Persona::getMail() { return _mail; }
bool Persona::getEliminado() { return _eliminado; }

// Setters
void Persona::setId(int id) {
    if (id >= 0) {
        _id = id;
    } else {
        cout << "ID incorrecto. Debe ser igual o mayor a 0. Se asignar 0 por defecto." << endl;
        _id = 0;
    }
}
void Persona::setNombre(const char* nombre) {
    if (nombre != nullptr && nombre[0] != '\0') {
        if (strlen(nombre) < 30) {
            strcpy(_nombre, nombre);
        } else {
            cout << "Nombre demasiado largo. Se cortara en 29 caracteres." << endl;
            strncpy(_nombre, nombre, 29);
            _nombre[29] = '\0';
        }
    } else {
        cout << "Nombre invalido. Se asignara 'Sin Nombre'." << endl;
        strcpy(_nombre, "Sin Nombre");
    }
}


void Persona::setApellido(const char* apellido) {
    if (apellido != nullptr && apellido[0] != '\0') {
        if (strlen(apellido) < 30) {
            strcpy(_apellido, apellido);

        } else {
             cout << "Apellido demasiado largo. Se cortara en 29 caracteres." << endl;
             strncpy(_apellido, apellido, 29);
        }
    } else {
        cout << "Apellido inválido. Se asignara 'Sin Apellido'." << endl;
        strcpy(_apellido, "Sin Apellido");
    }
}

void Persona::setTelefono(const char* telefono){
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

void Persona::setMail(const char* mail) {
    if (mail != nullptr && mail[0] != '\0') {
        if (strlen(mail) < 40) {
            strcpy(_mail, mail);
        } else {
            cout << "Mail demasiado largo. Se cortara en 39 caracteres." << endl;
            strncpy(_mail, mail, 39);
            _mail[39] = '\0';
        }
    } else {
        cout << "Mail invalido. Se asignara 'Sin mail'." << endl;
        strcpy(_mail, "Sin mail");
    }
}


void Persona::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}

// Método cargar
void Persona::Cargar(int id) {

    char nombre[30];
    char apellido[30];
    char telefono[20];
    char mail[40];


    setId(id);
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(60);
    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << "☕ PERFIL DE CLIENTE/EMPLEADO" << endl;
    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(60);
    restaurarColor();

    rlutil::setColor(PaletaCafe::CREMA);
    cout << "ID asignado: ";
    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << id << endl;

    imprimirPrompt("Ingrese nombre: ");
    rlutil::setColor(PaletaCafe::ESPUMA);
    cargarCadena(nombre, 30);
    setNombre(nombre);
    cargarCadena(nombre, 30);
    setNombre(nombre);

    imprimirPrompt("Ingrese apellido: ");
    rlutil::setColor(PaletaCafe::ESPUMA);
    cargarCadena(apellido, 30);
    setApellido(apellido);
//Se fuerza la carga de un telefono valido reutilizando la nueva validación general
    rlutil::setColor(PaletaCafe::ESPUMA);
    cargarCadenaObligatoria("Ingrese telefono: ", "El telefono es obligatorio. Intente nuevamente.", telefono, 20);
    setTelefono(telefono);

//Se fuerza la carga de un mail valido reutilizando la nueva validación general
    rlutil::setColor(PaletaCafe::ESPUMA);
    cargarCadenaObligatoria("Ingrese mail: ", "El mail es obligatorio. Intente nuevamente.", mail, 40);
    setMail(mail);

    _eliminado = false;
    rlutil::setColor(PaletaCafe::OK);
    cout << "Persona cargada correctamente." << endl;
    restaurarColor();
}

// Método Mostrar (Perfecto)
void Persona::Mostrar() {
    cout << "-----------------------------" << endl;
    cout << "ID Persona: " << _id << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Apellido: " << _apellido << endl;
    cout << "Telefono: "<<_telefono<<endl;
    cout << "Mail: "<<_mail <<endl;
    cout << "-----------------------------" << endl;
}
