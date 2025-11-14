#pragma once
#include <string>
#include "../Entities/DetallePedido.h"

class ArchivoDetallePedido{

private:
    std::string _nombreArchivo;

public:

    //Constructor

    ArchivoDetallePedido(std::string nombreArchivo = "DetallesPedidos.dat");

    //Métodos

    //Crear
    bool grabarRegistro(DetallePedido reg);

    //Leer por posición
    DetallePedido leerRegistro(int posicion);

    //Numero total de registros
    int contarRegistros();

    //Buscar la posición de un registro
    int buscarRegistro(int idDetallePedido);
    int buscarDetallePorPedidoYProducto(int idPedido, int idProducto);

    //Sobreescribir un registro
    bool modificarRegistro (DetallePedido reg, int posicion);

    //Revertir el archivo a una cantidad determinada de registros
    bool restaurarCantidadRegistros(int cantidadRegistros);

    //Listar
    void listar();

};
