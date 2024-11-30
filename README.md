# 🌌 Sistema Solar Interactivo en OpenGL

Este proyecto es una simulación interactiva del sistema solar desarrollada en **C++** utilizando **OpenGL**. Permite a los usuarios explorar y aprender sobre los planetas, sus órbitas y características, con elementos visuales y controles interactivos.

## 🖥️ Requisitos del sistema

- **Sistema operativo:** Windows 7 o superior.
- **Compilador:** Compatible con C++ (probado con Visual Studio 2019 o 2022).
- **Arquitectura:** Ejecución en **32 bits** (incluso si el sistema operativo es de 64 bits).
- **Librerías necesarias:**
  - OpenGL
  - GLUT
  - GLEW
  - Freeglut

---

## ⚙️ Configuración del entorno

1. **Instalar Visual Studio**
   - Descarga e instala [Visual Studio](https://visualstudio.microsoft.com/).
   - Asegúrate de incluir las herramientas para desarrollo en C++ durante la instalación.

2. **Descargar las librerías necesarias**
   - [GLEW](http://glew.sourceforge.net/)
   - [GLUT](https://www.opengl.org/resources/libraries/glut/)

3. **Configurar el proyecto**
   - Clona este repositorio:
     ```bash
     git clone https://github.com/tu-usuario/tu-repositorio.git
     ```
   - Abre el proyecto en Visual Studio.

4. **Configurar las librerías en Visual Studio**
   - Dirígete a `Propiedades del proyecto` > `Configuración del Vinculador` > `Entradas` y agrega las siguientes dependencias:
     - `glew32.lib`
     - `opengl32.lib`
     - `glut32.lib`
     - `freeglut.lib`
   - Ve a las propiedades de `C/C++` > `Directorios de Inclusión` y agrega las rutas de los archivos de encabezado (`.h`) de las librerías descargadas.
   - En las propiedades del `Vinculador` > `Directorios de Bibliotecas`, agrega las rutas a las librerías compiladas (`.lib`).

5. **Forzar compilación en 32 bits**
   - Ve a `Propiedades del proyecto` > `Configuración del Compilador`.
   - Cambia la configuración de la plataforma a **x86** (32 bits).

---

## 📂 Estructura del proyecto

- **main.cpp**: Archivo principal que inicializa el sistema solar.
- **planeta.cpp / planeta.h**: Clase que representa a los planetas y lunas.
- **cargaimagen.cpp / cargaimagen.h**: Carga y maneja texturas en formato BMP.
- **images/**: Carpeta que contiene las texturas para los planetas y el fondo.

---

## 🚀 Ejecución

1. Compila el proyecto en Visual Studio.
2. Ejecuta el programa directamente desde Visual Studio (modo Debug o Release).
3. Usa los controles para interactuar con el sistema solar:
   - **Espacio**: Inicia/detiene la animación.
   - **Teclas O/M/L**: Controla las órbitas, lunas y etiquetas.
   - **Scroll del mouse**: Controla el zoom.
   - **Teclas 1/2/3**: Cambia el ángulo de la cámara.

---

## 🛠️ Personalización

- **Agregar más planetas o lunas**: Usa la clase `Planeta` y crea nuevas instancias en `main.cpp`.
- **Cambiar texturas**: Reemplaza las imágenes BMP en la carpeta `images` con texturas de tu elección.

---

## 👥 Contribuidores

- Juan Carlos Piero Sánchez Cabanillas 
- David Tandazo Rodríguez  
- Valeria Nicol Gabancho Davila
- Yrving Alfredo Carranza Pérez
- Medrik Álvaro Huerta Quispe 

---

Si necesitas ayuda adicional, ¡no dudes en contactarnos! 🎉
