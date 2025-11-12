#pragma once

#include <string>
//#include "Prodcto.h"
#include "../Entities/Producto.h"


class ArchivoProducto {

private:
    std::string _nombreArchivo;

public:
    //Constructor

    ArchivoProducto(std::string nombreArchivo = "Productos.dat");


    //Métodos para interactuar con el archivo

    bool grabarRegistro(Producto reg);

    Producto leerRegistro (int posicion);

    int contarRegistros();

    int buscarRegistro(int idProducto);

    bool modificarRegistro (Producto reg, int posicion);

    void listar();
    void listarEliminados();
    bool hayProductosConEstadoEliminado(bool eliminado);



};
