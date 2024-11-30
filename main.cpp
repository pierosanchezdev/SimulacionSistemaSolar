#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include "cargaimagen.h"
#include "planeta.h"
#pragma comment(lib, "glew32.lib")

using namespace std;

// Variables globales para planetas, texturas y control de animación.
//Sol
Planeta sol(5.0, 0, 0, 0, 0, 0);

//Mercurio
Planeta mercurio(1.0, 7, 0, 4.74, 02.11, 0);

//Venus
Planeta venus(1.5, 11, 0, 3.50, 177.0, 0);

//Tierra
Planeta tierra(2.0, 16, 0, 2.98, 23.44, 0);
Planeta luna(.40, 3, 0, 5.40, 0, 0);

//Marte
Planeta marte(1.2, 21, 0, 2.41, 25.00, 0);
Planeta fobos(.20, 1.8, 0, 2.30, 0, 0);
Planeta deimos(.24, 2.4, 0, 3.60, 0, 0);

//Jupiter
Planeta jupiter(3.5, 28, 0, 1.31, 03.13, 0);
Planeta io(0.091, 5.9, 0, 2.00, 0, 0);
Planeta europa(.24, 4, 0, 4.40, 0, 0);
Planeta ganimides(.24, 4.7, 0, 5.00, 0, 0);
Planeta calisto(.24, 5.3, 0, 2.30, 0, 0);

//Saturno
Planeta saturno(3.0, 37, 0, 0.97, 26.70, 0);
Planeta tit(.75, 3.7, 0, 2.40, 0, 0);
Planeta rea(0.03819, 10.0, 0, 2.00, 0, 0);
Planeta japeto(0.036725, 12.0, 0, 1.75, 0, 0);
Planeta dione(0.02807, 14.0, 0, 2.25, 0, 0);

//Urano
Planeta urano(2.5, 45.5, 0, 0.68, 97.77, 0);

//Neptuno
Planeta neptuno(2.3, 53.6, 0, 0.54, 28.32, 0);

//Pluton
Planeta pluton(0.3, 59, 0, 0.47, 119.6, 0);

Planeta nix(.10, 1.5, 0, 5.00, 0, 0);
Planeta puc(.26, 2.9, 0, 7.00, 0, 0);
Planeta tri(.36, 3.2, 0, 3.40, 0, 0);

// Variables de control del estado de la simulación.
int animacionActiva = 0; // Controla si la animación está activa.
int orbitasGrandesActivas = 1; // Controla la visibilidad de las órbitas principales.
int pequenasOrbitasActivas = 1; // Controla la visibilidad de las órbitas de los satélites.
int activarLunas = 1; // Controla la visibilidad de las lunas.
int cambiarCamara = 0; // Controla el ángulo de la cámara.
int cuadrosPorSegundo = 0; // Controla los cuadros por segundo
int activarLeyenda = 0; // Controla las etiquetas de los planetas
int zoom = 50; // Zoom base
int logoEscenario = 1; // Controla si se muestra el logo inicial o el escenario principal.

float lightPos[] = { 0.0, 0.0, -75.0, 1.0 };
static float spotAngle = 40;
float spotDirection[] = { 1.0, 0.0, 0.0 };
static float spotExponent = 1.0;

/**
* Función para cargar una textura desde una imagen.
* @param imagen Puntero a la imagen cargada.
* @return Identificador de la textura generada.
*/
GLuint cargarTexturas(Imagen* imagen) {
	GLuint idTextura;
	glGenTextures(1, &idTextura);
	glBindTexture(GL_TEXTURE_2D, idTextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen->anchura, imagen->altura, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->pixeles);
	return idTextura;
}

GLuint texturaSol, texturaMercurio, texturaVenus, texturaTierra, texturaMarte, texturaJupiter, texturaSaturno, texturaUrano, texturaNeptuno, texturaPluton, staTexture, logTexture;

void convertirBitMapAString(void* fuente, const char* string) {
	const char* c;
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(fuente, *c);
}

/**
 * Función que configura los parámetros iniciales de OpenGL, incluidas texturas e iluminación.
 */
void setup(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	// Configuración de materiales y texturas.
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	// Carga texturas para los planetas y el logo.
	Imagen* sta = cargarBMP("images/estrellas.bmp");		staTexture = cargarTexturas(sta);		delete sta;
	Imagen* sol = cargarBMP("images/sol.bmp");		texturaSol = cargarTexturas(sol);		delete sol;
	Imagen* mercurio = cargarBMP("images/mercurio.bmp");	texturaMercurio = cargarTexturas(mercurio);		delete mercurio;
	Imagen* venus = cargarBMP("images/venus.bmp");		texturaVenus = cargarTexturas(venus);		delete venus;
	Imagen* tierra = cargarBMP("images/tierra.bmp");		texturaTierra = cargarTexturas(tierra);		delete tierra;
	Imagen* marte = cargarBMP("images/marte.bmp");		texturaMarte = cargarTexturas(marte);		delete marte;
	Imagen* jupiter = cargarBMP("images/jupiter.bmp");	texturaJupiter = cargarTexturas(jupiter);		delete jupiter;
	Imagen* saturno = cargarBMP("images/saturno.bmp");		texturaSaturno = cargarTexturas(saturno);		delete saturno;
	Imagen* urano = cargarBMP("images/urano.bmp");		texturaUrano = cargarTexturas(urano);		delete urano;
	Imagen* neptuno = cargarBMP("images/neptuno.bmp");	texturaNeptuno = cargarTexturas(neptuno);		delete neptuno;
	Imagen* pluton = cargarBMP("images/pluton.bmp");		texturaPluton = cargarTexturas(pluton);		delete pluton;
	Imagen* log = cargarBMP("images/logo.bmp");		logTexture = cargarTexturas(log);		delete log;

	// Configuración de iluminación.
	glEnable(GL_LIGHTING);
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 }; // Luz ambiental.
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 }; // Luz difusa y especular.
	float globAmb[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
}

//Configuración de trayecto de orbitas
void trayectoOrbitas(void) {
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glutWireTorus(0.001, mercurio.distancia, 100.0, 100.0);
	glutWireTorus(0.001, venus.distancia, 100.0, 100.0);
	glutWireTorus(0.001, tierra.distancia, 100.0, 100.0);
	glutWireTorus(0.001, marte.distancia, 100.0, 100.0);
	glutWireTorus(0.001, jupiter.distancia, 100.0, 100.0);
	glutWireTorus(0.001, saturno.distancia, 100.0, 100.0);
	glutWireTorus(0.001, urano.distancia, 100.0, 100.0);
	glutWireTorus(0.001, neptuno.distancia, 100.0, 100.0);
	glutWireTorus(0.001, pluton.distancia, 100.0, 100.0);
	glPopMatrix();
}

/**
 * Función para cargar y mostrar el logo inicial en la pantalla.
 * Utiliza una textura cargada previamente para dibujar un polígono cuadrado.
 */
void cargarLogoInicial(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia el buffer de color y profundidad.
	glLoadIdentity(); // Restablece la matriz de modelado.

	glEnable(GL_TEXTURE_2D); // Habilita las texturas en 2D.
	glBindTexture(GL_TEXTURE_2D, logTexture); // Asocia la textura del logo inicial.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Configura el filtro de textura para reducir tamaño.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Configura el filtro de textura para ampliar tamaño.

	// Dibuja un polígono con la textura del logo aplicado.
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-100, -100, -100);
	glTexCoord2f(1.0, 0.0); glVertex3f(100, -100, -100);
	glTexCoord2f(1.0, 1.0); glVertex3f(100, 100, -100);
	glTexCoord2f(0.0, 1.0); glVertex3f(-100, 100, -100);
	glEnd();

	glutSwapBuffers(); // Intercambia los buffers para mostrar el contenido.
}

/**
 * Función principal para renderizar el sistema solar.
 * Incluye los planetas, sus órbitas, etiquetas y cámaras.
 */
void dibujarEscenario(void) {
	cuadrosPorSegundo++; // Incrementa el contador de cuadros renderizados.

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Limpia el buffer de color y profundidad.
	glLoadIdentity(); // Restablece la matriz de modelado.

	// Configura la cámara según el estado actual.
	if (cambiarCamara == 0)gluLookAt(0.0, zoom, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (cambiarCamara == 1)gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (cambiarCamara == 2)gluLookAt(0.0, zoom, 0.00001, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	if (orbitasGrandesActivas == 1) trayectoOrbitas(); // Dibuja las órbitas principales si están activadas.

	GLUquadric* cuadrica;
	cuadrica = gluNewQuadric();

	// Renderiza el sol.
	glPushMatrix();
	glRotatef(sol.orbita, 0.0, 1.0, 0.0); // Aplica la rotación de la órbita.
	glTranslatef(sol.distancia, 0.0, 0.0); // Traslada al centro del sistema.
	if (activarLeyenda == 1) { // Muestra la etiqueta del sol si está activada.
		glRasterPos3f(-1.2, 7.0, 0.0);
		glColor3ub(255, 255, 255);
		convertirBitMapAString(GLUT_BITMAP_HELVETICA_12, "Sol");
	}
	glPushMatrix();
	glRotatef(sol.ejeInclinacion, 1.0, 0.0, 0.0); // Inclina el eje del sol.
	glRotatef(sol.ejeAnimacion, 0.0, 1.0, 0.0); // Rota el sol sobre su eje.
	glRotatef(90.0, 1.0, 0.0, 0.0); // Ajusta la orientación del sol.
	glEnable(GL_TEXTURE_2D); // Habilita las texturas para el sol.
	glBindTexture(GL_TEXTURE_2D, texturaSol); // Asocia la textura del sol.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(cuadrica, 1); // Asocia la textura al objeto cuadrático.
	gluSphere(cuadrica, sol.radio, 20.0, 20.0); // Dibuja el sol como una esfera.
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	//Mercurio
	glPushMatrix();
	glRotatef(mercurio.orbita, 0.0, 1.0, 0.0);
	glTranslatef(mercurio.distancia, 0.0, 0.0);
	if (activarLeyenda == 1) {
		glRasterPos3f(0.0, 3, 0.0);
		glColor3ub(255, 255, 255);
		convertirBitMapAString(GLUT_BITMAP_HELVETICA_12, "Mercurio");
	}
	glPushMatrix();
	glRotatef(mercurio.ejeInclinacion, 1.0, 0.0, 0.0);
	glRotatef(mercurio.ejeAnimacion, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaMercurio);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(cuadrica, 1);
	gluSphere(cuadrica, mercurio.radio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	//Venus
	glPushMatrix();
	glRotatef(venus.orbita, 0.0, 1.0, 0.0);
	glTranslatef(venus.distancia, 0.0, 0.0);
	if (activarLeyenda == 1) {
		glRasterPos3f(0.0, 3, 0.0);
		glColor3ub(255, 255, 255);
		convertirBitMapAString(GLUT_BITMAP_HELVETICA_12, "Venus");
	}
	glPushMatrix();
	glRotatef(venus.ejeInclinacion, 1.0, 0.0, 0.0);
	glRotatef(venus.ejeAnimacion, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaVenus);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(cuadrica, 1);
	gluSphere(cuadrica, venus.radio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	//Tierra
	glPushMatrix();
	glRotatef(tierra.orbita, 0.0, 1.0, 0.0);
	glTranslatef(tierra.distancia, 0.0, 0.0);
	if (activarLeyenda == 1) {
		glRasterPos3f(0.0, 3, 0.0);
		glColor3ub(255, 255, 255);
		convertirBitMapAString(GLUT_BITMAP_HELVETICA_12, "Tierra");
	}
	glPushMatrix();
	glRotatef(tierra.ejeInclinacion, 1.0, 0.0, 0.0);
	glRotatef(tierra.ejeAnimacion, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaTierra);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(cuadrica, 1);
	gluSphere(cuadrica, tierra.radio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	if (pequenasOrbitasActivas == 1) {
		luna.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1) {
		luna.dibujarLuna();
	}
	glPopMatrix();

	//Marte
	glPushMatrix();
	glRotatef(marte.orbita, 0.0, 1.0, 0.0);
	glTranslatef(marte.distancia, 0.0, 0.0);
	if (activarLeyenda == 1) {
		glRasterPos3f(0.0, 3, 0.0);
		glColor3ub(255, 255, 255);
		convertirBitMapAString(GLUT_BITMAP_HELVETICA_12, "Marte");
	}
	glPushMatrix();
	glRotatef(marte.ejeInclinacion, 1.0, 0.0, 0.0);
	glRotatef(marte.ejeAnimacion, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaMarte);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(cuadrica, 1);
	gluSphere(cuadrica, marte.radio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	if (pequenasOrbitasActivas == 1) {
		fobos.dibujarOrbitaPequeña();
		deimos.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1) {
		fobos.dibujarLuna();
		deimos.dibujarLuna();
	}
	glPopMatrix();

	//Júpiter
	glPushMatrix();
	glRotatef(jupiter.orbita, 0.0, 1.0, 0.0);
	glTranslatef(jupiter.distancia, 0.0, 0.0);
	if (activarLeyenda == 1) {
		glRasterPos3f(0.0, 4.4, 0.0);
		glColor3ub(255, 255, 255);
		convertirBitMapAString(GLUT_BITMAP_HELVETICA_12, "Jupiter");
	}
	glPushMatrix();
	glRotatef(jupiter.ejeInclinacion, 1.0, 0.0, 0.0);
	glRotatef(jupiter.ejeAnimacion, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaJupiter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(cuadrica, 1);
	gluSphere(cuadrica, jupiter.radio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	if (pequenasOrbitasActivas == 1) {
		io.dibujarOrbitaPequeña();
		europa.dibujarOrbitaPequeña();
		ganimides.dibujarOrbitaPequeña();
		calisto.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1) {
		io.dibujarLuna();
		europa.dibujarLuna();
		ganimides.dibujarLuna();
		calisto.dibujarLuna();
	}
	glPopMatrix();

	//Saturno
	glPushMatrix();
	glRotatef(saturno.orbita, 0.0, 1.0, 0.0);
	glTranslatef(saturno.distancia, 0.0, 0.0);
	if (activarLeyenda == 1) {
		glRasterPos3f(0.0, 4.4, 0.0);
		glColor3ub(255, 255, 255);
		convertirBitMapAString(GLUT_BITMAP_HELVETICA_12, "Saturno");
	}
	glPushMatrix();
	glRotatef(saturno.ejeInclinacion, 1.0, 0.0, 0.0);
	glRotatef(saturno.ejeAnimacion, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaSaturno);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(cuadrica, 1);
	gluSphere(cuadrica, saturno.radio, 20.0, 20.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3ub(158, 145, 137);
	glRotatef(-63.0, 1.0, 0.0, 0.0);
	glutWireTorus(0.2, 6.0, 30.0, 30.0);
	glutWireTorus(0.4, 5.0, 30.0, 30.0);
	glPopMatrix();
	if (pequenasOrbitasActivas == 1) {
		tit.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1) {
		tit.dibujarLuna();
	}
	glPopMatrix();

	glColor3ub(255, 255, 255);		//FIXES SHADING ISSUE

	//Urano
	glPushMatrix();
	glRotatef(urano.orbita, 0.0, 1.0, 0.0);
	glTranslatef(urano.distancia, 0.0, 0.0);
	if (activarLeyenda == 1) {
		glRasterPos3f(0.0, 4.4, 0.0);
		glColor3ub(255, 255, 255);
		convertirBitMapAString(GLUT_BITMAP_HELVETICA_12, "Urano");
	}
	glPushMatrix();
	glRotatef(urano.ejeInclinacion, 1.0, 0.0, 0.0);
	glRotatef(urano.ejeAnimacion, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaUrano);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(cuadrica, 1);
	gluSphere(cuadrica, urano.radio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	if (pequenasOrbitasActivas == 1) {
		puc.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1) {
		puc.dibujarLuna();
	}
	glPopMatrix();

	//Neptunon
	glPushMatrix();
	glRotatef(neptuno.orbita, 0.0, 1.0, 0.0);
	glTranslatef(neptuno.distancia, 0.0, 0.0);
	if (activarLeyenda == 1) {
		glRasterPos3f(0.0, 4.4, 0.0);
		glColor3ub(255, 255, 255);
		convertirBitMapAString(GLUT_BITMAP_HELVETICA_12, "Neptuno");
	}
	glPushMatrix();
	glRotatef(neptuno.ejeInclinacion, 1.0, 0.0, 0.0);
	glRotatef(neptuno.ejeAnimacion, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaNeptuno);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(cuadrica, 1);
	gluSphere(cuadrica, neptuno.radio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	if (pequenasOrbitasActivas == 1) {
		tri.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1) {
		tri.dibujarLuna();
	}
	glPopMatrix();

	//Pluton
	glPushMatrix();
	glRotatef(pluton.orbita, 0.0, 1.0, 0.0);
	glTranslatef(pluton.distancia, 0.0, 0.0);
	if (activarLeyenda == 1) {
		glRasterPos3f(0.0, 3.0, 0.0);
		glColor3ub(255, 255, 255);
		convertirBitMapAString(GLUT_BITMAP_HELVETICA_12, "Pluton");
	}
	glPushMatrix();
	glRotatef(pluton.ejeInclinacion, 1.0, 0.0, 0.0);
	glRotatef(pluton.ejeAnimacion, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaPluton);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(cuadrica, 1);
	gluSphere(cuadrica, pluton.radio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	if (pequenasOrbitasActivas == 1) {
		nix.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1) {
		nix.dibujarLuna();
	}
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, staTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_POLYGON);
	glTexCoord2f(-1.0, 0.0); glVertex3f(-200, -200, -100);
	glTexCoord2f(2.0, 0.0); glVertex3f(200, -200, -100);
	glTexCoord2f(2.0, 2.0); glVertex3f(200, 200, -100);
	glTexCoord2f(-1.0, 2.0); glVertex3f(-200, 200, -100);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, staTexture);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-200, -83, 200);
	glTexCoord2f(8.0, 0.0); glVertex3f(200, -83, 200);
	glTexCoord2f(8.0, 8.0); glVertex3f(200, -83, -200);
	glTexCoord2f(0.0, 8.0); glVertex3f(-200, -83, -200);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers(); // Intercambia los buffers para mostrar el contenido renderizado.
}

/**
 * Dibuja el logo inicial o el escenario principal según el estado.
 * Llama a `cargarLogoInicial` o `dibujarEscenario`.
 */
void dibujarEscenariosEnOrden(void) {
	if (logoEscenario == 1) {
		cargarLogoInicial();
	}
	else {
		dibujarEscenario();
	}
}

/**
 * Función para redimensionar la ventana y ajustar la proyección.
 * @param w Ancho actual de la ventana.
 * @param h Altura actual de la ventana.
 */
void redimensionar(int w, int h) {
	glViewport(0, 0, w, h); // Ajusta el área de visualización al nuevo tamaño de la ventana.
	glMatrixMode(GL_PROJECTION); // Cambia al modo de matriz de proyección.
	glLoadIdentity(); // Restablece la matriz de proyección.
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0); // Define un volumen de visualización en perspectiva.
	glMatrixMode(GL_MODELVIEW); // Cambia de nuevo al modo de matriz de modelado.
}

/**
 * Función para manejar la animación de los planetas y lunas.
 * Incrementa las posiciones orbitales y de rotación de los objetos en el sistema solar.
 * @param n Parámetro requerido por GLUT, no se usa directamente.
 */
void animaciones(int n) {
	if (animacionActiva) { // Solo se ejecuta si la animación está activa
		// Incrementa las órbitas de los planetas y satélites.
		mercurio.orbita += mercurio.velocidadOrbita;
		venus.orbita += venus.velocidadOrbita;
		tierra.orbita += tierra.velocidadOrbita;
		marte.orbita += marte.velocidadOrbita;
		jupiter.orbita += jupiter.velocidadOrbita;
		saturno.orbita += saturno.velocidadOrbita;
		urano.orbita += urano.velocidadOrbita;
		neptuno.orbita += neptuno.velocidadOrbita;
		pluton.orbita += pluton.velocidadOrbita;
		luna.orbita += luna.velocidadOrbita;
		fobos.orbita += fobos.velocidadOrbita;
		deimos.orbita += deimos.velocidadOrbita;
		io.orbita += io.velocidadOrbita;
		europa.orbita += europa.velocidadOrbita;
		ganimides.orbita += ganimides.velocidadOrbita;
		calisto.orbita += calisto.velocidadOrbita;
		tit.orbita += tit.velocidadOrbita;
		nix.orbita += nix.velocidadOrbita;
		puc.orbita += puc.velocidadOrbita;
		tri.orbita += tri.velocidadOrbita;
		if (mercurio, venus, tierra, marte, jupiter, saturno, urano, neptuno, pluton, luna, fobos, deimos, io, europa, ganimides, calisto, tit, nix, puc, tri.orbita > 360.0) {
			mercurio, venus, tierra, marte, jupiter, saturno, urano, neptuno, pluton, luna, fobos, deimos, io, europa, ganimides, calisto, tit, nix, puc, tri.orbita -= 360.0;
		}
		mercurio.ejeAnimacion += 10.0;
		venus.ejeAnimacion += 10.0;
		tierra.ejeAnimacion += 10.0;
		marte.ejeAnimacion += 10.0;
		jupiter.ejeAnimacion += 10.0;
		saturno.ejeAnimacion += 10.0;
		urano.ejeAnimacion += 10.0;
		neptuno.ejeAnimacion += 10.0;
		pluton.ejeAnimacion += 10.0;
		if (mercurio, venus, tierra, marte, jupiter, saturno, urano, neptuno, pluton.ejeAnimacion > 360.0) {
			mercurio, venus, tierra, marte, jupiter, saturno, urano, neptuno, pluton.ejeAnimacion -= 360.0;
		}
		glutPostRedisplay(); // Solicita redibujar la escena.
		glutTimerFunc(30, animaciones, 1); // Configura el temporizador para llamar a esta función nuevamente.
	}
}

/**
 * Función para manejar los clics del ratón.
 * @param boton Botón presionado (GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, etc.).
 * @param estado Estado del botón (GLUT_DOWN o GLUT_UP).
 * @param x Coordenada X del cursor al hacer clic.
 * @param y Coordenada Y del cursor al hacer clic.
 */
void controlRaton(int boton, int estado, int x, int y)
{
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
		if (logoEscenario) logoEscenario = 0;

	if (boton == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN) exit(0);
	glutPostRedisplay();
}

/**
 * Función para manejar la rueda del ratón (scroll).
 * Ajusta el nivel de zoom del sistema solar.
 * @param wheel Dirección de la rueda (1 para arriba, -1 para abajo).
 * @param direction Dirección del movimiento.
 * @param x Coordenada X del cursor.
 * @param y Coordenada Y del cursor.
 */
void ruedaDelRaton(int wheel, int direction, int x, int y)
{
	if (direction > 0 && zoom < 100) zoom++;
	if (direction < 0 && zoom > -75) zoom--;
	glutPostRedisplay();
}

/**
 * Función para manejar la entrada del teclado.
 * Permite interactuar con la simulación mediante teclas específicas.
 * @param key Tecla presionada.
 * @param x Coordenada X del cursor al presionar la tecla.
 * @param y Coordenada Y del cursor al presionar la tecla.
 */
void detectarEntradaTeclado(unsigned char key, int x, int y) {
	switch (key) {
	case 27: exit(0); break;
	case ' ': if (animacionActiva) animacionActiva = 0; else { animacionActiva = 1; animaciones(1); } break;
	case 'o': if (pequenasOrbitasActivas) pequenasOrbitasActivas = 0; else pequenasOrbitasActivas = 1; glutPostRedisplay(); break;
	case 'O': if (orbitasGrandesActivas) orbitasGrandesActivas = 0; else orbitasGrandesActivas = 1; glutPostRedisplay(); break;
	case 'm': if (activarLunas) activarLunas = 0; else activarLunas = 1; glutPostRedisplay(); break;
	case 'M': if (activarLunas) activarLunas = 0; else activarLunas = 1; glutPostRedisplay(); break;
	case 'l': if (activarLeyenda) activarLeyenda = 0; else activarLeyenda = 1; glutPostRedisplay(); break;
	case 'L': if (activarLeyenda) activarLeyenda = 0; else activarLeyenda = 1; glutPostRedisplay(); break;
	case '1': cambiarCamara = 0; glutPostRedisplay(); break;
	case '2': cambiarCamara = 1; glutPostRedisplay(); break;
	case '3': cambiarCamara = 2; glutPostRedisplay(); break;
	}
}

/**
 * Función para mostrar las instrucciones de uso en la consola.
 * Ayuda al usuario a interactuar con la simulación.
 */
void panelIntrucciones(void) {
	cout << "PRESIONA Barra espaciadora para Iniciar / Detener la simulación" << endl;
	cout << "PRESIONA Escape para salir de la simulación" << endl;
	cout << "Presiona O para mostrar/ocultar los trayectos de orbitas grandes" << endl;
	cout << "Presiona o para mostrar/ocultar los trayectos de orbitas pequeñas" << endl;
	cout << "PRESIONA M/m para mostrar/ocultar las lunas." << endl;
	cout << "PRESIONA L/l para mostrar/ocultar las etiquetas" << endl;
	cout << "PRESIONA 1, 2 o 3 para cambiar los ángulos de cámara" << endl;
	cout << "USA la rueda del mouse para alejar/acercar la cámara" << endl;
}

/**
 * Función principal para inicializar GLUT, configurar el contexto y entrar al bucle principal.
 */
int main(int argc, char** argv) {
	panelIntrucciones();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("Solar System");
	glutDisplayFunc(dibujarEscenariosEnOrden);
	glutReshapeFunc(redimensionar);
	glutMouseFunc(controlRaton);
	glutKeyboardFunc(detectarEntradaTeclado);
	glutMouseWheelFunc(ruedaDelRaton);
	glewExperimental = GL_TRUE;
	glewInit();

	setup();
	glutMainLoop();
}