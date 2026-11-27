# Simulador de Sistema operativo

Proyecto desarrollado para la materia de Sistemas Operativos. Consiste en un simulador de gestión de memoria (Mejor Ajuste y Peor Ajuste) junto con un planificador de CPU Round Robin, con una interfaz visual en consola utilizando la librería `libcaca´.

## Requisitos previos

Para compilar y ejecutar este proyecto, necesitas tener instalado:
1. **Windows** (el proyecto está configurado para este sistema).
2. **MSYS2** (Instalado preferentemente en la ruta por defecto 'C:\msys64').
3. **Visual Studio Code** con la extensión **C/C++** de Microsoft.

## Instalacion de dependencias

Abre la terminal de **MSYS2 UCRT64** y ejecuta los siguientes comandos para instalar el compilador y la librería gráfica:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-libcaca
pacman -S mingw-w64-ucrt-x86_64-pkg-config
