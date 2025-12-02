#include <iostream>
#include <cstring>
#include <cstdio>

#include "../../Headers/Entities/Fecha.h"
#include "../../Headers/Entities/Pedido.h"
#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;

// Constructor
Pedido::Pedido(int idPedido,
               int idCliente,
               int idEmpleado,
               int nroMesa,
               Fecha fecha,
               float subtotal,
               int porcentajeDesc,
               int puntuacion,
               bool eliminado)
    : _idPedido(idPedido),
      _idCliente(idCliente),
      _idEmpleado(idEmpleado),
      _fecha(fecha),
      _eliminado(eliminado)
{
    setNroMesa(nroMesa, false);
    setSubtotal(subtotal);
    setPorcentajeDescuento(porcentajeDesc);
    setPuntuacionServicio(puntuacion, false);
}

// Getters
int Pedido::getIdPedido() { return _idPedido; }
int Pedido::getIdCliente() { return _idCliente; }
int Pedido::getIdEmpleado() { return _idEmpleado; }
int Pedido::getNroMesa() { return _nroMesa; }
Fecha Pedido::getFecha() { return _fecha; }
float Pedido::getSubtotal() { return _subtotal; }
int Pedido::getPorcentajeDescuento() { return _porcentajeDescuento; }

float Pedido::getTotal() {
    float factorDescuento = _porcentajeDescuento / 100.0f;
    float montoDescuento = _subtotal * factorDescuento;
    float totalCalculado = _subtotal - montoDescuento;
    return (totalCalculado > 0.0f) ? totalCalculado : 0.0f;
}

int Pedido::getPuntuacionServicio() { return _puntuacionServicio; }
bool Pedido::getEliminado() { return _eliminado; }

// Setters
void Pedido::setNroMesa(int nro, bool mostrarAdvertencia) {
    if (nro > 0) {
        _nroMesa = nro;
    } else if (mostrarAdvertencia)  {
        cout << "Numero de mesa incorrecto. Debe ser mayor a 0. Se asignara 1." << endl;
        _nroMesa = 1;

    }
}

void Pedido::setFecha(Fecha fecha) {
    _fecha = fecha;
}

void Pedido::setSubtotal(float subtotal) {
    if (subtotal >= 0.0f) {
        _subtotal = subtotal;
    } else {
        cout << "El subtotal debe ser un numero positivo o cero. Se asignara 0.0 por defecto." << endl;
        _subtotal = 0.0f;
    }
}

void Pedido::setPorcentajeDescuento(int porcentaje) {
    if (porcentaje >= 0 && porcentaje <= 100) {
        _porcentajeDescuento = porcentaje;
    } else {
        cout << "Porcentaje de descuento invalido (debe ser entre 0 y 100) . Se asignara 0% de descuento por defecto" << endl;
            porcentaje = 0;
    }
}

void Pedido::setPuntuacionServicio(int puntuacion, bool mostrarAdvertencia) {
    if (puntuacion >= 1 && puntuacion <= 5) {
        _puntuacionServicio = puntuacion;
    } else if (mostrarAdvertencia) {
        cout << "La puntuacion debe ser un valor entre 1 y 5 inclusive. Se le asignara 3 por defecto." << endl;
        _puntuacionServicio = 3;
    }
}

void Pedido::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}


// Método Cargar
void Pedido::Cargar(int idPedido, int idCliente, int idEmpleado) {
    _idPedido = idPedido;
    _idCliente = idCliente;
    _idEmpleado = idEmpleado;

    cout << "ID del Pedido asignado: " << _idPedido << endl;
    cout << "ID del Cliente asignado: "<< _idCliente<<endl;
    cout << "ID del Empleado asignado: "<<_idEmpleado<<endl;


// Uso la fecha actual del sistema para garantizar coherencia temporal
    _fecha.asignarFechaActual();
    cout << "Fecha del pedido establecida automáticamente: ";
    _fecha.Mostrar();
    int mesa, puntaje, porcDesc;


    //Numero de mesa
    while(true){
        mesa = ingresarEntero("Ingrese el numero de mesa (mayor a 0): ");
        if(mesa > 0){
            break;
        }
        cout << "ERROR: El numero de mesa ingresado debe ser mayor a 0"<<endl;
    }
    setNroMesa(mesa);

    //Inicializo el subtotal del pedido en cero (se recalcula al agregar productos)
    setSubtotal(0.0f);
    cout << "Subtotal inicializado en $0. Se actualizará al cargar los productos." << endl;

    //Porcentaje de descuento entre 0 y 100.
    while(true){
        porcDesc = ingresarEntero("Ingrese el porcentaje de descuento (0 a 100, sin %): ");
        if(porcDesc >= 0 && porcDesc <=100){
            break;

        } else {
        cout<< "ERROR: El porcentaje debe estar entre 0 y 100."<<endl;
        }
    }

    setPorcentajeDescuento(porcDesc);


    //Puntaje del servicio
    while(true){
        puntaje = ingresarEntero("Ingrese el puntaje del servicio (1 a 5): ");
        if (puntaje >= 1 && puntaje <= 5){
            break;
        } else {
        cout<< "ERROR: El puntaje debe ser un numero entre 1 y 5."<<endl;
        }
    }
    setPuntuacionServicio(puntaje);

    _eliminado = false;
    cout << "Pedido cargado correctamente." << endl;
}

// Método Mostrar
void Pedido::Mostrar() {
    cout << "--- DATOS DEL PEDIDO ---" << endl;
    cout << "ID del Pedido: " << _idPedido << endl;
    cout << "ID del Cliente: " << _idCliente << endl;
    cout << "ID del Empleado: " << _idEmpleado << endl;
    cout << "Fecha: ";
    _fecha.Mostrar();
    cout << "Numero de mesa: " << _nroMesa << endl;
    cout << "Subtotal: $" << _subtotal << endl;
    cout << "Descuento Aplicado: " << _porcentajeDescuento << "%" << endl;
    cout << "TOTAL A PAGAR: $" << getTotal() << endl;
    cout << "Puntuacion del servicio: " << _puntuacionServicio << endl;
    cout << "-------------------------" << endl;
}
