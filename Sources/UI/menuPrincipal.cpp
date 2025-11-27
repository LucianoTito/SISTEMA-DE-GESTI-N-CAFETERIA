#include <iostream>
#include <cstdlib>

#include "../../Headers/UI/menuPrincipal.h"
#include "../../Headers/UI/menuGestionProductos.h"
#include "../../Headers/UI/menuGestionClientes.h"
#include "../../Headers/UI/menuEmpleados.h"
#include"../../Headers/Entities/Empleado.h"
#include "../../Headers/UI/menuPedidos.h"
#include "../../Headers/UI/reportes.h"
#include "../../Headers/UI/configuraciones.h"
#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;

void menuPrincipal() {

    int opcion;

    while (true) {
        system("cls");

        cout << "---- MENU PRINCIPAL DE VENCO CAFE ----" << endl;
        cout << "======================================" << endl;
        cout << "1. GESTION DE PRODUCTOS" << endl;
        cout << "2. GESTION DE CLIENTES" << endl;
        cout << "3. GESTION DE EMPLEADOS" << endl;
        cout << "4. GESTION DE PEDIDOS" << endl;
        cout << "----------------------------------------" << endl;
        cout << "5. REPORTES" << endl;
        cout << "6. CONFIGURACIONES" << endl;
        cout << "----------------------------------------" << endl;
        cout << "0. SALIR" << endl;
        cout << "======================================" << endl;
        cout << endl;

        opcion = ingresarEntero("SELECCIONE UNA OPCION: ");

        system("cls");

        // Se asume que solo se necesita pausar si hubo un error de opción.
        bool mostrarPausa = false;

        switch (opcion) {
            case 1:

                menuProductos();
                break;
            case 2:

                menuClientes();
                break;
            case 3:

                menuEmpleados();
                break;
            case 4:

                menuPedidos();
                break;
            case 5:

                menuReportes();
                break;
            case 6:

                menuConfiguraciones();
                break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                return;
            default:
                cout << "Opcion incorrecta. Ingrese solo un numero y vuelva a intentarlo." << endl;
                mostrarPausa = true;
                break;
        }
        // Evitamos una pausa extra al volver de un menú; solo se muestra si hubo un error.
        if (mostrarPausa) {
            system("pause");
        }
    }
}
