#include<iostream>
#include "../../Headers/Utilidades/Tablas.h"

using namespace std;


// Imprimo una línea doble usando '='.
//La uso para separar secciones importantes, como títulos de reportes.
void lineaDoble(int n) {
    for (int i = 0; i < n; i++) cout << "=";
    cout << endl;
}


// Imprimo una línea simple usando '-'.
void lineaSimple(int n) {
    for (int i = 0; i < n; i++) cout << "-";
    cout << endl;
}




// COLUMNAS )
//  - Col1: ancho 5
//  - Col2: ancho 8
//  - Col3: ancho 18
//  - Col4: ancho 18
//  - Col5: ancho 10
//
// Los valores llegan como cadenas const char*, porque así puedo usar sprintf()
// antes de llamar a esta función cuando necesito imprimir números.
void imprimirFila5(const char* c1,
                   const char* c2,
                   const char* c3,
                   const char* c4,
                   const char* c5) {

    const int a1 = 5;   // POS
    const int a2 = 8;   // ID
    const int a3 = 18;  // APELLIDO / PRODUCTO
    const int a4 = 18;  // NOMBRE
    const int a5 = 10;  // EXTRA (puntos / pedidos)

    cout << "|| "
         << left << setw(a1) << c1 << " || "
         << left << setw(a2) << c2 << " || "
         << left << setw(a3) << c3 << " || "
         << left << setw(a4) << c4 << " || "
         << left << setw(a5) << c5 << " ||"
         << endl;
}

void imprimirFila4(const char* c1, const char* c2, const char* c3, const char* c4) {

    const int a1 = 5;   // POS
    const int a2 = 8;   // ID
    const int a3 = 28;  // PRODUCTO
    const int a4 = 15;  // CANT.

    cout << "|| "
         << left << setw(a1) << c1 << " || "
         << left << setw(a2) << c2 << " || "
         << left << setw(a3) << c3 << " || "
         << left << setw(a4) << c4 << " ||"
         << endl;
}

void imprimirFila2(const char* c1, const char* c2) {

    const int a1 = 18; // MES
    const int a2 = 15; // TOTAL

    cout << "|| "
         << left  << setw(a1) << c1 << " || "
         << right << setw(a2) << c2 << " ||"
         << endl;
}

//MPLEMENTACIÓN PARA PEDIDOS ---
void imprimirFilaPedido(const char* id, const char* fecha, const char* idCli, const char* idEmp, const char* total) {
    // Anchos personalizados para que entre la fecha (10 chars) y se vea bien
    const int wId = 8;
    const int wFecha = 12;
    const int wCli = 12;
    const int wEmp = 12;
    const int wTotal = 12;

    cout << "|| "
         << left << setw(wId) << id << " | "
         << left << setw(wFecha) << fecha << " | "
         << left << setw(wCli) << idCli << " | "
         << left << setw(wEmp) << idEmp << " | "
         << right << setw(wTotal) << total << " ||"
         << endl;
}

void imprimirFilaEmpleado(const char* id, const char* nombre, const char* apellido, const char* telefono, const char* mail, const char* puesto) {
    const int wId = 6;
    const int wNombre = 15;
    const int wApellido = 15;
    const int wTel = 15;
    const int wMail = 35;
    const int wPuesto = 15;

    cout << "|| "
         << left << setw(wId) << id << " | "
         << left << setw(wNombre) << nombre << " | "
         << left << setw(wApellido) << apellido << " | "
         << left << setw(wTel) << telefono << " | "
         << left << setw(wMail) << mail << " | "
         << left << setw(wPuesto) << puesto << " ||"
         << endl;
}
