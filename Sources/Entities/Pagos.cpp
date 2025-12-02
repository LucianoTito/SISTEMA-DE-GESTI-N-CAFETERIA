#include <iostream>
#include <cstdio>
//#include "Pagos.h"
#include "../../Headers/Entities/Pagos.h"
//#include "Fecha.h"
#include "../../Headers/Entities/Fecha.h"
#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;

Pagos::Pagos (int idPago,
              int idPedido,
              Fecha fechaPago,
              int metodoPago,
              float montoPagado
              )
              :_idPago(idPago),
               _idPedido(idPedido),
               _fechaPago(fechaPago)
               {
                   setMetodoPago(metodoPago, false);
                   setMontoPagado(montoPagado);
               }
//Getters
int Pagos::getIdPago() { return _idPago; }
int Pagos::getIdPedido() { return _idPedido;}
Fecha Pagos::getFechaPago(){ return _fechaPago; }
int Pagos::getMetodoPago() { return _metodoPago; }
float Pagos::getMontoPagado() { return _montoPagado; }

//Setters

void Pagos::setFechaPago(Fecha fecha){
_fechaPago= fecha;
}
void Pagos::setMetodoPago(int metodo, bool mostrarAviso) {

    if (metodo >= 1 && metodo <= 3) {
        _metodoPago = metodo;
    } else if(mostrarAviso) {
        cout << "Metodo de pago invalido. No se realizaron cambios." << endl;

    }
}
void Pagos::setMontoPagado(float monto) {

    if (monto >= 0.0f) {
        _montoPagado = monto;
    } else {
        cout << "Monto pagado no puede ser negativo. Se asignara 0.0." << endl;
        _montoPagado = 0.0f;
    }
}


//Método cargar

void Pagos::Cargar(int idPago, int idPedido, float montoAPagar, const Fecha& fechaPedido){

_idPago = idPago;
_idPedido = idPedido;

cout << "ID Pago asignado: " << _idPago << endl;
cout << "ID Pedido asociado: " << _idPedido << endl;


// Asigna el monto recibido
    setMontoPagado(montoAPagar); // Usa el setter para validar (>= 0)
    cout << "Monto a pagar asignado: $" << montoAPagar << endl;



// Se utiliza la fecha actual del sistema para registrar el pago
    _fechaPago.asignarFechaActual();
    if (_fechaPago < fechaPedido){
        cout << "AVISO: La fecha del sistema es anterior a la del pedido." << endl;
        cout << "Se ajusta la fecha de pago a la fecha del pedido para mantener coherencia." << endl;
        _fechaPago = fechaPedido;
    }
    cout << "Fecha de pago establecida: ";
    _fechaPago.Mostrar();

int metd;


cout<< "Ingrese el metodo de pago: "<<endl;
cout<<endl;
cout<< "1. Efectivo"<<endl;
cout<< "2. Tarjeta"<<endl;
cout<< "3. Transferencia"<<endl;

while(true) {
    metd = ingresarEntero("Ingrese una opcion (1-3): ");

    if(metd >= 1 && metd <=3){
        break;
    }
    cout<< "ERROR: El metodo de pago debe ser 1, 2 o 3."<<endl;
}

setMetodoPago(metd);



cout << "Pago cargado correctamente." << endl;

}

//Método mostrar

void Pagos::Mostrar(){
cout << "--- DATOS DEL PAGO ---" << endl;

cout << "ID del Pago: "<<_idPago<<endl;
cout << "ID del Pedido Asociado: "<<_idPedido<<endl;
cout <<"Fecha pago : ";
_fechaPago.Mostrar();
cout << "Método Pago: ";

    switch (_metodoPago) {
        case 1: cout << "Efectivo"; break;
        case 2: cout << "Tarjeta"; break;
        case 3: cout << "Transferencia"; break;
        default: cout << "Desconocido/Invalido"; break;
    }
    cout << endl;
cout << "Monto a pagado: $"<<_montoPagado<<endl;
cout << "--------------------------------" << endl;

}


