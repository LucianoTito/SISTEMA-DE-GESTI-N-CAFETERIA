#include <iostream>
#include <ctime>

#include "../../Headers/Entities/Fecha.h"
#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;

//Constructor
Fecha::Fecha(int dia, int mes, int anio) {
    _dia = dia;
    _mes = mes;
    _anio = anio;
}

//Getters
int Fecha::getDia() {
    return _dia;
}
int Fecha::getMes() {
    return _mes;
}
int Fecha::getAnio() {
    return _anio;
}

//Setters
void Fecha::setDia(int dia) {
    if (dia > 0 && dia < 32) {
        _dia = dia;
    } else {
        cout << "Dato incorrecto. El numero de día debe ser entre 1 y 31. Se asignara 1 por defecto." << endl;
        _dia = 1;
    }
}
void Fecha::setMes(int mes) {
    if (mes > 0 && mes < 13) {
        _mes = mes;
    } else {
        cout << "Dato incorrecto. El numero de mes  debe ser entre 1 y 12. Se asignara 1 por defecto." << endl;
        _mes = 1;
    }
}
void Fecha::setAnio(int anio) {

    if (anio >= 2025 && anio <= 2050) {
        _anio = anio;
    } else {
        cout << "Año fuera del rango valido (2025 - 2050). Se asignara 2025 por defecto." << endl;
        _anio = 2025;
    }
}

// pido los datos al usuario por consola
void Fecha::Cargar() {
    int d, m, a; // Variables temporales

//Día
while(true){
     d = ingresarEntero("DIA: ");
    if (d >= 1 && d <=31){
        break;
    }else {
            cout<< "ERROR: El dia debe estar entre 1 y 31. \n";
    }
}
setDia(d);


//Mes
while(true) {
     m = ingresarEntero("MES: ");
    if (m >= 1 && m <=12) {
        break;
    }else{
            cout<< "ERROR: El mes debe estar entre 1 y 12. \n";
    }
}
setMes(m);


//Año
while(true){

     a = ingresarEntero("ANIO: ");
    if (a >= 2025 && a <= 2050){
        break;
    }else {
    cout<< "ERROR: El anio debe estar entre 2025 y 2050.\n";
    }
}
setAnio(a);

}

// Mostrar()
void Fecha::Mostrar() {
    cout << _dia << "/" << _mes << "/" << _anio << endl;
}

// Asigna al objeto la fecha actual del sistema (día, mes y año)
void Fecha::asignarFechaActual() {
    time_t tiempoActual = time(nullptr);
    tm* fechaSistema = localtime(&tiempoActual);

    _dia = fechaSistema->tm_mday;
    _mes = fechaSistema->tm_mon + 1;    // tm_mon arranca en 0, por eso se suma 1
    _anio = fechaSistema->tm_year + 1900; // tm_year cuenta desde 1900
}

/*Sobrecarga de operadores: Estas funciones permiten comparar objetos Fecha de manera
natural usando los operadores relacionales (<, >, <=, >=, ==, !=).
Esto hace posible filtrar o ordenar fechas, como en el
reporte de productos vendidos por período.
  */

// Operador de igualdad
bool Fecha::operator==(const Fecha& f) const {
    return _dia == f._dia && _mes == f._mes && _anio == f._anio;
}

// Operador de desigualdad
bool Fecha::operator!=(const Fecha& f) const {
    return !(*this == f);
}

// Operador menor
bool Fecha::operator<(const Fecha& f) const {
    if (_anio != f._anio) return _anio < f._anio;
    if (_mes  != f._mes)  return _mes  < f._mes;
    return _dia < f._dia;
}

// Operador mayor
bool Fecha::operator>(const Fecha& f) const {
    return f < *this;
}

// Operador menor o igual
bool Fecha::operator<=(const Fecha& f) const {
    return !(*this > f);
}

// Operador mayor o igual
bool Fecha::operator>=(const Fecha& f) const {
    return !(*this < f);
}


