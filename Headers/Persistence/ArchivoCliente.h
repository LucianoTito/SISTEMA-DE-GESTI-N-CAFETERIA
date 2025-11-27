#pragma once
#include <string>
#include "../Entities/Cliente.h"


class ArchivoCliente {

private:

    std::string _nombreArchivo;

public:

    //Constructor

    ArchivoCliente(std::string nombreArchivo = "Clientes.dat");

    //Métodos CRUD

    //Create
    bool grabarRegistro (Cliente reg);

    //Read
    Cliente leerRegistro (int posicion);

    //Contar
    int contarRegistros();

    //Buscar
    int buscarRegistro (int idCliente);

    //Update
    bool modificarRegistro (Cliente reg, int posicion);

    //Listar
    void listar();
    void listarEliminados();
    bool hayClientesConEstadoEliminado(bool eliminado);
    void listarOrdenadosPorApellido();

};
