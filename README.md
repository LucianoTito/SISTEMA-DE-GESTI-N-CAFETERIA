<div align="center">
  <h1>☕ Sistema de Gestión para Cafetería</h1>
  
  <p>
    <strong>Una solución integral de gestión comercial (ERP) desarrollada en C++ moderno.</strong>
  </p>

  <p>
    <a href="#-demo">Ver Demo</a> •
    <a href="#-características-técnicas">Tecnologías</a> •
    <a href="#-instalación">Instalación</a> •
    <a href="#-contacto">Contacto</a>
  </p>

  <p>
    <img src="https://img.shields.io/badge/C%2B%2B-14%2F17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++"/>
    <img src="https://img.shields.io/badge/Paradigma-POO-orange?style=for-the-badge" alt="POO"/>
    <img src="https://img.shields.io/badge/Persistencia-Binaria-lightgrey?style=for-the-badge&logo=files" alt="Binary Files"/>
    <img src="https://img.shields.io/badge/IDE-Code%3A%3ABlocks-green?style=for-the-badge&logo=codeblocks" alt="CodeBlocks"/>
  </p>
</div>

---

## 🚀 Sobre el Proyecto

Este sistema es una aplicación de consola de alto rendimiento diseñada para administrar el flujo operativo de una cafetería. A diferencia de los ejercicios académicos estándar, este proyecto se enfoca en la **persistencia de datos real**, la **arquitectura en capas** y una **experiencia de usuario (UX)** cuidada mediante el manejo avanzado de buffers y colores en consola.

El objetivo fue simular un entorno de producción donde la integridad de los datos (Clientes, Stock, Facturación) y la escalabilidad del código son prioritarios.

## 📹 Demo

> *Visualización del flujo de toma de pedidos y generación de tickets.*

![Demo del Sistema](https://via.placeholder.com/800x400?text=AQUI+VA+TU+GIF+DEL+SISTEMA+FUNCIONANDO)
*(Nota: Reemplaza este link por la URL de tu GIF real)*

---

## 🧩 Funcionalidades Clave

### 📦 Gestión de Inventario y Ventas
* **CRUD Completo:** Alta, Baja y Modificación de Productos y Empleados con validaciones en tiempo real.
* **Control de Stock:** Validación automática de disponibilidad antes de confirmar pedidos.
* **Sistema de Ventas:** Generación de pedidos vinculando Cliente + Empleado + Múltiples productos.

### 📊 Reportes y Business Intelligence
* **Reportes Financieros:** Recaudación histórica y filtrada por períodos.
* **Rankings:** Algoritmos de ordenamiento para mostrar "Clientes VIP" y productos más vendidos.
* **Historial:** Consulta de tickets pasados con detalle desglosado.

### 🎨 Interfaz de Usuario (TUI)
* **Diseño Visual:** Uso de librería `rlutil` para manipulación de colores y posicionamiento de cursor.
* **Navegación Fluida:** Menús interactivos controlados por teclado sin necesidad de "limpiar pantalla" forzoso (flickering reducido).

---

## 🛠 Características Técnicas (Under the Hood)

Este proyecto demuestra el dominio de conceptos avanzados de C++ y buenas prácticas de ingeniería de software:

* **Programación Orientada a Objetos (POO):** Uso extensivo de Clases, Herencia, Encapsulamiento y Polimorfismo.
* **Gestión de Memoria:** Manejo eficiente de punteros y asignación dinámica de memoria durante la ejecución de los menús.
* **Persistencia de Datos:** Implementación de un motor de persistencia propio utilizando archivos binarios (`.dat`) y punteros de archivo (`FILE*`) para lectura/escritura aleatoria y secuencial.
* **Arquitectura Limpia:** Estricta separación de responsabilidades:
    * `Entities`: Modelado de datos.
    * `Persistence`: Capa de acceso a datos (DAO).
    * `UI`: Capa de presentación y validación de entrada.

---

## 📋 Prerrequisitos

Para ejecutar este proyecto necesitarás:

* **Sistema Operativo:** Windows (recomendado por uso de librerías específicas de consola).
* **Compilador:** MinGW / G++ con soporte para C++14 o superior.
* **IDE (Opcional):** Code::Blocks (proyecto configurado nativamente).

---

## 💻 Instalación y Ejecución

### Opción A: Code::Blocks (Recomendado)

1. **Clonar** el repositorio.
2. Abrir el archivo `Sistema de Gestión.cbp`.
3. Compilar y Ejecutar (**F9**).

### Opción B: Compilación Manual (G++)

Si prefieres usar la terminal, asegúrate de enlazar todos los archivos fuente correctamente desde la raíz del proyecto:

```bash
g++ Sources/*.cpp Sources/Entities/*.cpp Sources/Persistence/*.cpp Sources/UI/*.cpp Sources/Utilidades/*.cpp -o sistema_cafeteria.exe
./sistema_cafeteria.exe
```

---

## 🏗️ Estructura del Proyecto

```text
Sistema de Gestión/
│
├── Headers/          # Definición de Clases y Prototipos (.h)
│   ├── Entities/     # Modelos (Cliente, Producto, etc.)
│   ├── Persistence/  # Manejadores de Archivos (Clases Archivo*)
│   └── UI/           # Lógica de Interfaz y Menús
│
├── Sources/          # Implementación de la Lógica (.cpp)
│   ├── Entities/     
│   ├── Persistence/  
│   └── UI/           
│
├── Data/             # Archivos binarios de base de datos (generados al ejecutar)
└── main.cpp          # Punto de entrada

💻 Instalación y Ejecución
Opción A: Code::Blocks (Recomendado)
Clonar el repositorio.

Abrir el archivo Sistema de Gestión.cbp.

Compilar y Ejecutar (F9).

Opción B: Compilación Manual (G++)
Si prefieres usar la terminal, asegúrate de enlazar todos los archivos fuente:

g++ Sources/*.cpp Sources/Entities/*.cpp Sources/Persistence/*.cpp Sources/UI/*.cpp Sources/Utilidades/*.cpp -o sistema_cafeteria.exe
./sistema_cafeteria.exe

👨‍💻 Autor
Luciano Facundo Tito Cedrón Software Developer | C++ Enthusiast

<p> <a href="https://www.google.com/search?q=https://www.linkedin.com/in/lucianotito/" target="_blank"> <img src="https://www.google.com/search?q=https://img.shields.io/badge/LinkedIn-Connect-blue%3Fstyle%3Dfor-the-badge%26logo%3Dlinkedin" alt="LinkedIn"/> </a> <a href="mailto:lucianotitocedron@gmail.com"> <img src="https://www.google.com/search?q=https://img.shields.io/badge/Email-Contactame-red%3Fstyle%3Dfor-the-badge%26logo%3Dgmail%26logoColor%3Dwhite" alt="Email"/> </a> </p>

<p align="center">
  <sub>Proyecto desarrollado en el marco de la Tecnicatura Universitaria en Programación (UTN FRGP) - 2025.</sub>
</p>
