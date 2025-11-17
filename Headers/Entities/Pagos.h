#pragma once
#include "Fecha.h"

class Pagos {
private:
    int _idPago;
    int _idPedido;
    Fecha _fechaPago;
    int _metodoPago;  // Forma de pago (Ej: 1=Efectivo, 2=Tarjeta, 3=Transferencia, etc.)
    float _montoPagado;

public:
    // Constructor
    Pagos(int idPago = 0,
          int idPedido = 0,
          Fecha fechaPago = Fecha(),
          int metodoPago = 0,
          float montoPagado = 0.0f);

    // Getters
    int getIdPago();
    int getIdPedido();
    Fecha getFechaPago();
    int getMetodoPago();
    float getMontoPagado();

    //Setters

    void setFechaPago(Fecha fecha);
    void setMetodoPago(int metodo, bool mostrarAviso = true);
    void setMontoPagado(float monto);

    // Métodos
    // Cargar recibe los IDs generados externamente
    void Cargar(int idPago, int idPedido, float montoAPagar);
    void Mostrar();
};
