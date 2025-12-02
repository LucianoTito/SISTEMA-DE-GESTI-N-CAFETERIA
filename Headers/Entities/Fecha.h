#pragma once

class Fecha {

private:
    int _dia, _mes, _anio;

public:

    // Constructor
    Fecha(int dia = 1, int mes = 1, int anio = 2025);

    // Getters
    int getDia();
    int getMes();
    int getAnio();

    // Setters
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    // Métodos de la clase
    void Cargar();
    void Mostrar();
    void asignarFechaActual();

 //Sobrecarga de operadores

    bool operator==(const Fecha& f) const;  // Igualdad
    bool operator!=(const Fecha& f) const;  // Desigualdad
    bool operator<(const Fecha& f)  const;  // Menor
    bool operator>(const Fecha& f)  const;  // Mayor
    bool operator<=(const Fecha& f) const;  // Menor o igual
    bool operator>=(const Fecha& f) const;  // Mayor o igual
};
