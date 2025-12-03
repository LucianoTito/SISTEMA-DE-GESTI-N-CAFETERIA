#include <iostream>
#include <iomanip>

#include "../../Headers/Utilidades/Tablas.h"

using namespace std;

// ==========================================
// PALETA Y ESTILO GENERAL
// ==========================================

void restaurarColor() {
    rlutil::resetColor();
}

void limpiarConsola() {
    rlutil::cls();
}

void pausarConsola(const string& mensaje) {
    cin.ignore(10000, '\n');
    rlutil::setColor(PaletaCafe::CREMA);
    cout << mensaje;
    restaurarColor();
    rlutil::anykey();
}

void imprimirTituloDecorado(const string& titulo, int ancho) {
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ancho);
    rlutil::setColor(PaletaCafe::ESPUMA);
    int padding = (ancho - static_cast<int>(titulo.size())) / 2;
    if (padding < 0) padding = 0;
    cout << string(padding, ' ') << titulo << endl;
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ancho);
    restaurarColor();
}

void imprimirSubtituloDecorado(const string& subtitulo, int ancho) {
    rlutil::setColor(PaletaCafe::CREMA);
    cout << string((ancho - static_cast<int>(subtitulo.size())) / 2, ' ') << subtitulo << endl;
    restaurarColor();
}

void imprimirMensajeOk(const string& mensaje) {
    rlutil::setColor(PaletaCafe::OK);
    cout << "✅ " << mensaje << endl;
    restaurarColor();
}

void imprimirMensajeAdvertencia(const string& mensaje) {
    rlutil::setColor(PaletaCafe::ADVERTENCIA);
    cout << "⚠️  " << mensaje << endl;
    restaurarColor();
}

void imprimirMensajeError(const string& mensaje) {
    rlutil::setColor(PaletaCafe::ERROR);
    cout << "❌ " << mensaje << endl;
    restaurarColor();
}

void imprimirPrompt(const string& prompt) {
    rlutil::setColor(PaletaCafe::CREMA);
    cout << prompt;
    restaurarColor();
}

void imprimirBannerCafe() {
    // Margen izquierdo para centrar el diseño
    string m = "        ";

    // 1. EL HUMO (Color: HUMO)
    rlutil::setColor(PaletaCafe::HUMO);
    cout << m << "      (  )   (   )  ) " << endl;
    cout << m << "       ) (   )  (  (  " << endl;
    cout << m << "       ( )  (    ) )  " << endl;

    // 2. EL BORDE SUPERIOR (Color: BASE)
    rlutil::setColor(PaletaCafe::BASE);
    cout << m << "      ___________    " << endl;

    // 3. CUERPO DE LA TAZA CON ESPUMA Y ASA MEJORADA
    // Línea 1: Superficie de la espuma
    cout << m << "     (";                           // Borde izq (BASE)
    rlutil::setColor(PaletaCafe::ESPUMA); cout << "..........."; // Espuma (ESPUMA)
    rlutil::setColor(PaletaCafe::BASE);   cout << ")   " << endl; // Borde der (BASE)

    // Línea 2: Cuerpo superior + Inicio del asa curvada
    cout << m << "     |";                           // Pared izq
    rlutil::setColor(PaletaCafe::ESPUMA); cout << "..........."; // Relleno espuma
    rlutil::setColor(PaletaCafe::BASE);   cout << "|-. " << endl; // Pared der + inicio asa

    // Línea 3: Cuerpo medio + Parte externa del asa (creando el hueco)
    cout << m << "     |";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << "...........";
    rlutil::setColor(PaletaCafe::BASE);   cout << "|  \\" << endl; // El hueco se forma a la izquierda de la '\'

    // Línea 4: Cuerpo medio bajo + Parte vertical del asa
    cout << m << "     |";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << "...........";
    rlutil::setColor(PaletaCafe::BASE);   cout << "|   |" << endl; // El hueco es evidente aquí

    // Línea 5: Cuerpo inferior + Curva baja del asa
    cout << m << "     |";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << "...........";
    rlutil::setColor(PaletaCafe::BASE);   cout << "| _/" << endl;

    // Línea 6: Base de la taza + Cierre del asa
    cout << m << "      \\_________/-'  " << endl;

    restaurarColor();
    cout << endl; // Un salto de línea extra para separar del menú
}
// ==========================================
// FUNCIONES DE LINEAS
// ==========================================

void lineaDoble(int n) {
    rlutil::setColor(PaletaCafe::BASE);
    for (int i = 0; i < n; i++) cout << "=";
    restaurarColor();
    cout << endl;
}


void lineaSimple(int n) {
    rlutil::setColor(PaletaCafe::BASE);
    for (int i = 0; i < n; i++) cout << "-";
    restaurarColor();
    cout << endl;
}

// ==========================================
// FILAS GENERICAS (LEGACY)
// ==========================================

void imprimirFila5(const char* c1, const char* c2, const char* c3, const char* c4, const char* c5) {
    const int a1 = 5;
    const int a2 = 8;
    const int a3 = 18;
    const int a4 = 18;
    const int a5 = 10;

    // Ancho total estimado: ~81 caracteres
    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(a1) << c1;
    rlutil::setColor(PaletaCafe::BASE); cout << " || ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(a2) << c2;
    rlutil::setColor(PaletaCafe::BASE); cout << " || ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(a3) << c3;
    rlutil::setColor(PaletaCafe::BASE); cout << " || ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(a4) << c4;
    rlutil::setColor(PaletaCafe::BASE); cout << " || ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(a5) << c5;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor();
    cout << endl;
}

void imprimirFila4(const char* c1, const char* c2, const char* c3, const char* c4) {
    const int a1 = 5;
    const int a2 = 8;
    const int a3 = 28;
    const int a4 = 15;

    // Ancho total estimado: ~74 caracteres
    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(a1) << c1;
    rlutil::setColor(PaletaCafe::BASE); cout << " || ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(a2) << c2;
    rlutil::setColor(PaletaCafe::BASE); cout << " || ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(a3) << c3;
    rlutil::setColor(PaletaCafe::BASE); cout << " || ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(a4) << c4;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor();
    cout << endl;
}

void imprimirFila2(const char* c1, const char* c2) {
    const int a1 = 18;
    const int a2 = 15;

    // Ancho total estimado: ~45 caracteres
    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(a1) << c1;
    rlutil::setColor(PaletaCafe::BASE); cout << " || ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(a2) << c2;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor();
    cout << endl;
}

// ==========================================
// FILAS ESPECIFICAS (DEFINITIVAS)
// ==========================================

// Usada en: MenuPedidos
// Ancho Total: 74 caracteres
void imprimirFilaPedido(const char* id, const char* fecha, const char* idCli, const char* idEmp, const char* total) {
    const int wId = 8;
    const int wFecha = 12;
    const int wCli = 12;
    const int wEmp = 12;
    const int wTotal = 12;

    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wFecha) << fecha;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wCli) << idCli;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wEmp) << idEmp;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wTotal) << total;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor();
    cout << endl;
}

// Usada en: Reportes de Pagos
// Ancho Total: 78 caracteres (alineado a otros listados)
void imprimirFilaPago(const char* idPago, const char* idPedido, const char* fecha, const char* metodo, const char* monto) {
    const int wIdPago = 8;
    const int wIdPedido = 10;
    const int wFecha = 12;
    const int wMetodo = 16;
    const int wMonto = 12;

    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wIdPago) << idPago;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wIdPedido) << idPedido;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wFecha) << fecha;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wMetodo) << metodo;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wMonto) << monto;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor();
    cout << endl;
}

// Usada en: MenuEmpleados
// Ancho Total: 122 caracteres
void imprimirFilaEmpleado(const char* id, const char* nombre, const char* apellido, const char* telefono, const char* mail, const char* puesto) {
    const int wId = 6;
    const int wNombre = 15;
    const int wApellido = 15;
    const int wTel = 15;
    const int wMail = 35;
    const int wPuesto = 15;

    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wNombre) << nombre;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wApellido) << apellido;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wTel) << telefono;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wMail) << mail;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wPuesto) << puesto;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor();
    cout << endl;
}

// Usada en: MenuGestionProductos
// Ancho Total: 81 caracteres
void imprimirFilaProducto(const char* id, const char* nombre, const char* precio, const char* stock) {
    const int wId = 6;
    const int wNombre = 35;
    const int wPrecio = 15;
    const int wStock = 10;

    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wNombre) << nombre;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wPrecio) << precio;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wStock) << stock;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor();
    cout << endl;
}

// Usada en: MenuGestionClientes
// Ancho Total: 94 caracteres (Perfecto)
void imprimirFilaCliente(const char* id, const char* nombre, const char* apellido, const char* telefono, const char* mail) {
    const int wId = 6;
    const int wNom = 15;
    const int wApe = 15;
    const int wTel = 15;
    const int wMail = 25;

    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wNom) << nombre;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wApe) << apellido;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wTel) << telefono;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wMail) << mail;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor();
    cout << endl;
}

// Usada en: Reportes (Recaudacion)
// Ancho Total: 50 caracteres (Ajustado)
void imprimirFilaRecaudacion(const char* mes, const char* total) {
    const int wMes = 20;
    const int wTotal = 21; // Ajustado para sumar 50 con los bordes

    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wMes) << mes;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wTotal) << total;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor();
    cout << endl;
}

// Usada en: Reportes (Ranking Productos)
// Ancho Total: 75 caracteres
void imprimirFilaRankingProductos(const char* pos, const char* id, const char* nombre, const char* cantidad) {
    const int wPos = 5;
    const int wId = 8;
    const int wNom = 37; // Aumentado para ajustar el ancho total a 75
    const int wCant = 10;

    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wPos) << pos;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wNom) << nombre;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wCant) << cantidad;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor();
    cout << endl;
}

// Usada en: Reportes (Ranking Empleados)
// Ancho Total: 80 caracteres
void imprimirFilaRankingEmpleados(const char* pos, const char* id, const char* apellido, const char* nombre, const char* cantidad) {
    const int wPos = 5;
    const int wId = 8;
    const int wApe = 20; // Ajustado para total 80
    const int wNom = 19; // Ajustado para total 80
    const int wCant = 10;

    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wPos) << pos;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wApe) << apellido;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wNom) << nombre;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wCant) << cantidad;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor();
    cout << endl;
}
