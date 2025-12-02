#pragma once
#include <iomanip>
#include <iostream>

using namespace std;

// Funciones generales de linea
void lineaDoble(int n = 80); // Valor por defecto para facilitar uso
void lineaSimple(int n = 80);

// Filas genéricas (Las que me pasaste)
void imprimirFila5(const char* c1, const char* c2, const char* c3, const char* c4, const char* c5);
void imprimirFila4(const char* c1, const char* c2, const char* c3, const char* c4);
void imprimirFila2(const char* c1, const char* c2);

//Fila específica para listados de pedidos (ajustada para Fechas y Montos)
void imprimirFilaPedido(const char* id, const char* fecha, const char* idCli, const char* idEmp, const char* total);

//Fila para empleados
void imprimirFilaEmpleado(const char* id, const char* nombre, const char* apellido, const char* telefono, const char* mail, const char* puesto);
