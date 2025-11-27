#pragma once
#include "Persona.h"


class Cliente : public Persona {

private:



public:
    // Constructor

    Cliente(int id = 0,
            const char* nombre = "Sin nombre",
            const char* apellido = "Sin apellido",
            const char* telefono = "Sin numero",
            const char* mail = "Sin mail",
            bool eliminado = false);




    // Métodos
    void Mostrar();
    void MostrarFila(const char* estado = nullptr);
    void Cargar(int id);
};
