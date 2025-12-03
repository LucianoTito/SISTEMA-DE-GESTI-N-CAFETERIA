#include <iostream>

#include "../../Headers/UI/menuPrincipal.h"
#include "../../Headers/UI/menuGestionProductos.h"
#include "../../Headers/UI/menuGestionClientes.h"
#include "../../Headers/UI/menuEmpleados.h"
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/UI/menuPedidos.h"
#include "../../Headers/UI/reportes.h"
#include "../../Headers/UI/configuraciones.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Tablas.h"

using namespace std;

// Definimos un ancho estándar para que el menú se vea centrado y robusto
const int ANCHO_MENU_PPAL = 60;

void menuPrincipal() {

    int opcion;

    while (true) {
        limpiarConsola();

        imprimirTituloDecorado("SISTEMA DE GESTION - BASTI CAFE", ANCHO_MENU_PPAL);

        imprimirSubtituloDecorado("Aromas, sabores y buena atencion", ANCHO_MENU_PPAL);
        cout << endl;

        // --- MODULOS OPERATIVOS ---
        rlutil::setColor(PaletaCafe::CREMA);
        cout << "   1.   GESTION DE PRODUCTOS  " << endl << endl;
        cout << "   2.   GESTION DE CLIENTES" << endl << endl;
        cout << "   3.   GESTION DE EMPLEADOS" << endl << endl;
        cout << "   4.   GESTION DE PEDIDOS" << endl << endl;

        // --- MODULOS ADMINISTRATIVOS ---
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(ANCHO_MENU_PPAL);
        cout << endl;
        rlutil::setColor(PaletaCafe::CREMA);
        cout << "   5.   REPORTES Y ESTADISTICAS" << endl << endl;
        cout << "   6.   CONFIGURACIONES Y RESPALDO" << endl << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(ANCHO_MENU_PPAL);

        // --- SALIDA ---
        rlutil::setColor(PaletaCafe::ESPUMA);
        cout << "   0.   SALIR DEL SISTEMA" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaDoble(ANCHO_MENU_PPAL);
        restaurarColor();



        imprimirSubtituloDecorado("SELECCIONE UNA OPCION", ANCHO_MENU_PPAL);

        rlutil::setColor(PaletaCafe::BASE);
        lineaDoble(ANCHO_MENU_PPAL);
        restaurarColor();


        opcion = ingresarEntero("  Opcion  >>> ");


        limpiarConsola();




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
                lineaDoble(ANCHO_MENU_PPAL);
                imprimirMensajeOk("Cerrando el sistema... Hasta luego!");
                lineaDoble(ANCHO_MENU_PPAL);
                return;
            default:
                imprimirMensajeError(">>> Opcion incorrecta. Intente nuevamente.");
                mostrarPausa = true;
                break;
        }

        if (mostrarPausa) {
            pausarConsola();
        }
    }
}
