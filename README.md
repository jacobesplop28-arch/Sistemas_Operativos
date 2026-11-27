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


#Cómo compilar

1-Abre la carpeta en Visual Studio Code.
2-Presiona Ctrl + Shift + B.
3-Se generará el archivo perrito_amarillo_franjas_moradas_SO.exe.
Nota: Si instalaste MSYS2 en otra ruta, edita las rutas en .vscode/tasks.json.

#Ejecución

Para ejecutarlo correctamente, ábrelo desde la terminal de MSYS2 UCRT64:

```bash
./perrito_amarillo_franjas_moradas_SO.exe

(Si haces doble clic en el explorador y marca error, copia libcaca-0.dll de C:\msys64\ucrt64\bin a la carpeta del ejecutable)


# Para saber como funciona el simulador, consulta el manual de usuario