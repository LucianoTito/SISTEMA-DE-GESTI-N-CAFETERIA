#pragma once
#include <cstring> // Necesario para strcpy en el .cpp

class Producto {

private:
    int _idProducto;
    char _nombre[50];
    float _precio;
    int _stock;
    bool _eliminado;

public:

    Producto(int idProducto = 0,
             const char* nombre = "Sin Nombre",
             float precio = 0.0f,
             int stock = 0,
             bool eliminado = false);

    // Getters
    int getIdProducto();
    const char* getNombre();
    float getPrecio();
    int getStock();
    bool getEliminado();

    // Setters
    void setIdProducto(int idProducto);
    void setNombre(const char* nombre);
    void setPrecio(float precio);
    void setStock(int stock);
    void setEliminado(bool eliminado);

    // Métodos
    void Mostrar();
    void Cargar(int idProducto);
    void MostrarFila(const char* estado = nullptr);
};
