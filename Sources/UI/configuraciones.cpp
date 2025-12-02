#include <iostream>
#include <cstdlib>
#include <cstring>

#include "../../Headers/UI/configuraciones.h"
#include "../../Headers/Utilidades/GestorArchivos.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Tablas.h"

using namespace std;

// Prototipos locales para simplificar la logica de los menús
void realizarBackupArchivo(const char* nombreReal, const char* nombreBkp);
void restaurarBackupArchivo(const char* nombreBkp, const char* nombreReal);
void procesarExportacion(bool exito, const char* nombreArchivo);

// Menu principal de configuraciones
void menuConfiguraciones() {
    int opcion;
    while(true){
        system("cls");
        lineaDoble(50);
        cout << "            CONFIGURACIONES DEL SISTEMA" << endl;
        lineaDoble(50);
        cout << "1. REALIZAR COPIA DE SEGURIDAD (.BKP)" << endl;
        cout << "2. RESTAURAR COPIA DE SEGURIDAD (.BKP)" << endl;
        cout << "3. EXPORTAR DATOS A EXCEL (CSV)" << endl;
        lineaSimple(50);
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        lineaDoble(50);

        opcion = ingresarEntero("SELECCIONE UNA OPCION: ");
        system("cls");

        switch(opcion){
            case 1: backupMenu(); break;            // Submenu de respaldos
            case 2: restaurarCopiaSeguridad(); break; // Submenu de restauracion
            case 3: exportarDatosCSV(); break;      // Submenu de exportacion
            case 0: return;
            default: cout << "Opcion incorrecta." << endl; break;
        }
        system("pause");
    }
}

// Submenu para crear backups
void backupMenu() {
    while (true) {
        system("cls");
        cout << "------- CREAR COPIAS DE SEGURIDAD -------" << endl;
        cout << "1. Clientes" << endl;
        cout << "2. Productos" << endl;
        cout << "3. Empleados" << endl;
        cout << "4. Pedidos" << endl;
        cout << "5. Detalles" << endl;
        cout << "6. Pagos" << endl;
        cout << "7. RESPALDAR TODO" << endl;
        cout << "0. Volver" << endl;
        cout << "-----------------------------------------" << endl;

        int opc = ingresarEntero("Opcion: ");
        if (opc == 0) return;

        // Llamamos al helper con el nombre del archivo original y el nombre que tendra el backup
        switch (opc) {
            case 1: realizarBackupArchivo("Clientes.dat", "Clientes.bkp"); break;
            case 2: realizarBackupArchivo("Productos.dat", "Productos.bkp"); break;
            case 3: realizarBackupArchivo("Empleados.dat", "Empleados.bkp"); break;
            case 4: realizarBackupArchivo("Pedidos.dat", "Pedidos.bkp"); break;
            case 5: realizarBackupArchivo("DetallesPedidos.dat", "DetallesPedidos.bkp"); break;
            case 6: realizarBackupArchivo("Pagos.dat", "Pagos.bkp"); break;
            case 7:
                // Respaldo masivo: llamamos a la funcion para cada archivo
                realizarBackupArchivo("Clientes.dat", "Clientes.bkp");
                realizarBackupArchivo("Productos.dat", "Productos.bkp");
                realizarBackupArchivo("Empleados.dat", "Empleados.bkp");
                realizarBackupArchivo("Pedidos.dat", "Pedidos.bkp");
                realizarBackupArchivo("DetallesPedidos.dat", "DetallesPedidos.bkp");
                realizarBackupArchivo("Pagos.dat", "Pagos.bkp");
                cout << endl << ">>> BACKUP COMPLETO FINALIZADO." << endl;
                break;
            default: cout << "Opcion invalida." << endl; break;
        }
        system("pause");
    }
}

// Submenu para restaurar datos (Sobreescribe archivos .dat)
void restaurarCopiaSeguridad(){
    while(true) {
        system("cls");
        cout << "------- RESTAURAR DESDE BACKUP -------" << endl;
        // ... (opciones de menu identicas al backup) ...
        cout << "1. Clientes" << endl;
        cout << "2. Productos" << endl;
        cout << "3. Empleados" << endl;
        cout << "4. Pedidos" << endl;
        cout << "5. Detalles" << endl;
        cout << "6. Pagos" << endl;
        cout << "7. RESTAURAR TODO" << endl;
        cout << "0. Volver" << endl;
        cout << "--------------------------------------" << endl;

        int opc = ingresarEntero("Opcion: ");
        if(opc == 0) return;

        // Advertencia de seguridad antes de sobreescribir datos
        char conf;
        cout << "CUIDADO: Esto sobreescribira los datos actuales con la copia. Continuar? (S/N): ";
        cin >> conf;
        if(conf != 'S' && conf != 's') continue;

        switch (opc){
            // Notese que aqui el origen es .bkp y el destino es .dat (al reves que en el backup)
            case 1: restaurarBackupArchivo("Clientes.bkp", "Clientes.dat"); break;
            case 2: restaurarBackupArchivo("Productos.bkp", "Productos.dat"); break;
            case 3: restaurarBackupArchivo("Empleados.bkp", "Empleados.dat"); break;
            case 4: restaurarBackupArchivo("Pedidos.bkp", "Pedidos.dat"); break;
            case 5: restaurarBackupArchivo("DetallesPedidos.bkp", "DetallesPedidos.dat"); break;
            case 6: restaurarBackupArchivo("Pagos.bkp", "Pagos.dat"); break;
            case 7:
                restaurarBackupArchivo("Clientes.bkp", "Clientes.dat");
                restaurarBackupArchivo("Productos.bkp", "Productos.dat");
                restaurarBackupArchivo("Empleados.bkp", "Empleados.dat");
                restaurarBackupArchivo("Pedidos.bkp", "Pedidos.dat");
                restaurarBackupArchivo("DetallesPedidos.bkp", "DetallesPedidos.dat");
                restaurarBackupArchivo("Pagos.bkp", "Pagos.dat");
                cout << endl << ">>> RESTAURACION COMPLETA FINALIZADA." << endl;
                break;
            default: cout << "Opcion invalida." << endl; break;
        }
        system("pause");
    }
}

// Submenu para exportar a CSV
void exportarDatosCSV(){
    while(true) {
        system("cls");
        cout << "------- EXPORTAR A CSV (EXCEL) -------" << endl;
        cout << "1. Clientes" << endl;
        cout << "2. Productos" << endl;
        cout << "3. Empleados" << endl;
        cout << "4. Pedidos" << endl;
        cout << "5. Detalles" << endl;
        cout << "6. Pagos" << endl;
        cout << "7. EXPORTAR TODO" << endl;
        cout << "0. Volver" << endl;
        cout << "--------------------------------------" << endl;

        int opc = ingresarEntero("Opcion: ");
        if(opc == 0) return;

        switch (opc){
            // procesarExportacion maneja el mensaje de exito/error
            case 1: procesarExportacion(exportarClientesCSV("Clientes.csv"), "Clientes.csv"); break;
            case 2: procesarExportacion(exportarProductosCSV("Productos.csv"), "Productos.csv"); break;
            case 3: procesarExportacion(exportarEmpleadosCSV("Empleados.csv"), "Empleados.csv"); break;
            case 4: procesarExportacion(exportarPedidosCSV("Pedidos.csv"), "Pedidos.csv"); break;
            case 5: procesarExportacion(exportarDetallesCSV("Detalles.csv"), "Detalles.csv"); break;
            case 6: procesarExportacion(exportarPagosCSV("Pagos.csv"), "Pagos.csv"); break;
            case 7:
                procesarExportacion(exportarClientesCSV("Clientes.csv"), "Clientes");
                procesarExportacion(exportarProductosCSV("Productos.csv"), "Productos");
                procesarExportacion(exportarEmpleadosCSV("Empleados.csv"), "Empleados");
                procesarExportacion(exportarPedidosCSV("Pedidos.csv"), "Pedidos");
                procesarExportacion(exportarDetallesCSV("Detalles.csv"), "Detalles");
                procesarExportacion(exportarPagosCSV("Pagos.csv"), "Pagos");
                cout << endl << ">>> EXPORTACION MASIVA COMPLETADA." << endl;
                break;
            default: cout << "Incorrecto." << endl; break;
        }
        system("pause");
    }
}

// --- HELPERS LOCALES DE UI ---
// Estas funciones se encargan de la interaccion con el usuario (mensajes)
// y delegan la accion real al GestorArchivos.

void realizarBackupArchivo(const char* nombreReal, const char* nombreBkp) {
    if (existeArchivo(nombreReal)) {
        if (copiarArchivoBinario(nombreReal, nombreBkp)) {
            cout << "[OK] Backup creado: " << nombreBkp << endl;
        } else {
            cout << "[ERROR] Fallo al crear backup de " << nombreReal << endl;
        }
    } else {
        cout << "[AVISO] Archivo no existe: " << nombreReal << " (omitido)" << endl;
    }
}

void restaurarBackupArchivo(const char* nombreBkp, const char* nombreReal) {
    if (existeArchivo(nombreBkp)) {
        if (copiarArchivoBinario(nombreBkp, nombreReal)) {
            cout << "[OK] Restaurado: " << nombreReal << endl;
        } else {
            cout << "[ERROR] Fallo al restaurar " << nombreReal << endl;
        }
    } else {
        cout << "[ERROR] No existe el backup: " << nombreBkp << endl;
    }
}

void procesarExportacion(bool exito, const char* nombreArchivo) {
    if (exito) cout << "[OK] Exportado: " << nombreArchivo << endl;
    else cout << "[ERROR] Fallo exportacion de " << nombreArchivo << endl;
}
