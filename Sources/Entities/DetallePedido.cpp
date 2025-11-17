#include<iostream>
//#include "DetallePedido.h"
#include "../../Headers/Entities/DetallePedido.h"
#include "../../Headers/Utilidades/Validaciones.h"
using namespace std;

DetallePedido::DetallePedido(int idDetalle,
                             int idPedido,
                             int idProducto,
                             int cantidad,
                             float precioUnitario
                             )
                             :_idDetalle(idDetalle),
                              _idPedido(idPedido),
                              _idProducto(idProducto)
                             {
                                 setCantidad(cantidad);
                                 setPrecioUnitario(precioUnitario);
                             }

            //Getters
int DetallePedido::getIdDetalle() { return _idDetalle; }
int DetallePedido::getIdPedido() { return _idPedido; }
int DetallePedido::getIdProducto() { return _idProducto; }
int DetallePedido::getCantidad(){ return _cantidad; }
float DetallePedido::getPrecioUnitario(){ return _precioUnitario; }


//Setters

void DetallePedido::setCantidad(int cantidad){
if(cantidad>=0){
    _cantidad = cantidad;
}else {
cout<< "La cantidad ingresada no puede ser negativa. Se le asignara 0 por defecto."<<endl;
_cantidad=0;
}
}

void DetallePedido::setPrecioUnitario (float precioUnitario){

if(precioUnitario>=0){
    _precioUnitario = precioUnitario;
} else {
cout<< "El precio no puede ser negativo. Se le asignara 0 por defecto."<<endl;
_precioUnitario=0;
}
}

//Método Cargar

void DetallePedido::Cargar(int idDetalle, int idPedido, int idProducto, int cantidad, float precioUnitario){

_idPedido = idPedido;
_idDetalle = idDetalle;
_idProducto = idProducto;

cout << "ID Detalle asignado: "<<_idDetalle<<endl;
cout << "ID Pedido asociado: "<<_idPedido<< endl;
cout <<"ID Producto asociado: "<<_idProducto<<endl;

setCantidad(cantidad);
setPrecioUnitario(precioUnitario);

cout << "Cantidad registrada: "<< _cantidad << endl;
cout << "Precio unitario registrado: $"<< _precioUnitario << endl;
cout << "Detalle de pedido cargado." << endl;
}


//Método mostrar

void DetallePedido::Mostrar(){

    cout << "--- DATOS DEL DETALLE DEL PEDIDO ---" << endl;

cout << "ID del Detalle: "<<_idDetalle<<endl;
cout << "ID del Pedido: "<<_idPedido<<endl;
cout <<"ID del Producto: "<<_idProducto<<endl;
cout << "Cantidad: "<<_cantidad<<endl;
cout << "Precio unitario: $"<<_precioUnitario<<endl;
cout << "--------------------------------" << endl;

}

