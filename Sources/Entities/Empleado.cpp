#include <iostream>
#include <cstring>
#include <cstdio>

#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;


Empleado::Empleado(int id,
                   const char* nombre,
                   const char* apellido,
                   bool eliminado,
                   const char* puesto)
    : Persona(id, nombre, apellido, eliminado)
{
    setPuesto(puesto);
}

// Getter específico de Empleado
const char* Empleado::getPuesto() { return _puesto; }

// Setter específico de Empleado
void Empleado::setPuesto(const char* puesto) {
    if (puesto != nullptr && puesto[0] != '\0') {
        if (strlen(puesto) < 20) {
            strcpy(_puesto, puesto);
        } else {
            cout << "Nombre del puesto demasiado largo. Se cortara en 19 caracteres." << endl;
            strncpy(_puesto, puesto, 19);
            _puesto[19] = '\0'; // Asegura el terminador
        }
    } else {
        cout << "Puesto invalido. Se asignara 'Sin puesto'." << endl;
        strcpy(_puesto, "Sin puesto");
    }

}

// Cargar
void Empleado::Cargar(int id) {
    char empleado[20]; // Buffer temporal para el puesto

    Persona::Cargar(id);

    cout << "Ingrese el puesto del empleado: ";
cargarCadena(empleado, 20);

setPuesto(empleado);

    cout << "Empleado cargado correctamente." << endl;
}

// Mostrar
void Empleado::Mostrar() {
    cout << "--- DATOS DEL EMPLEADO ---" << endl;

    Persona::Mostrar();

    cout << "Puesto: " << _puesto << endl;
    cout << "-------------------------" << endl;
}
