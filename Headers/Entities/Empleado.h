#pragma once

#include "Persona.h"


class Empleado : public Persona {

private:
    char _puesto[20];

public:

    //Constructor

    Empleado (int id = 0,
              const char* nombre = "Sin nombre",
              const char* apellido = "Sin apellido",
              const char* telefono = "Sin numero",
              const char* mail = "Sin mail",
              bool eliminado = false,
              const char* puesto = "Sin puesto" );

//Getters

const char* getPuesto();

//Setters

void setPuesto(const char* puesto);

//Métodos
void Cargar(int id);
void MostrarFila(const char* estado = nullptr);
void Mostrar();
};


