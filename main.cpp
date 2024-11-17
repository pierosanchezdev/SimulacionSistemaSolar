#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include "imageloader.h"
#pragma comment(lib, "glew32.lib")

using namespace std;

class Planeta{
public:
	float radio, distancia, orbita, velocidadOrbita, ejeInclinacion, ejeAnimacion;
	Planeta(float _radio, float _distancia, float _orbita, float _velocidadOrbita, float _ejeInclinacion, float _ejeAnimacion){
		radio = _radio;
		distancia = _distancia;
		orbita = _orbita;
		velocidadOrbita = _velocidadOrbita;
		ejeInclinacion = _ejeInclinacion;
		ejeAnimacion = _ejeAnimacion;
	}

	void dibujarOrbitaPequeña(void){
		glPushMatrix();
		glColor3ub(255, 255, 255);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glutWireTorus(0.001, distancia, 100.0, 100.0);
		glPopMatrix();
	}

	void dibujarLuna(void){
		GLUquadricObj *cuadrica;
		cuadrica = gluNewQuadric();
		glPushMatrix();
		glColor3ub(255, 255, 255);
		glRotatef(orbita, 0.0, 1.0, 0.0);
		glTranslatef(distancia, 0.0, 0.0);
		gluSphere(cuadrica, radio, 20.0, 20.0);
		glPopMatrix();
	}

};

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

int animacionActiva = 0;
int orbitasGrandesActivas = 1;
int pequenasOrbitasActivas = 1;
int activarLunas = 1;
int cambiarCamara = 0;
int cuadrosPorSegundo = 0;
int activarLeyenda = 0;
int zoom = 50;
int logoEscenario = 1;

float lightPos[] = { 0.0, 0.0, -75.0, 1.0 };
static float spotAngle = 40;
float spotDirection[] = { 1.0, 0.0, 0.0 };
static float spotExponent = 1.0;

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

GLuint texturaSol, texturaMercurio, texturaVenus, texturaTierra, texturaMarte, texturaJupiter, texturaSaturno, texturaUrano, texturaNeptuno, texturaPluton, staTexture, logTexture;

void writeBitmapString(void *font, char *string)
{
	char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void setup(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	//TEXUTRING SETUP
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	Image* sta = loadBMP("images/stars.bmp");		staTexture = loadTexture(sta);		delete sta;
	Image* sol = loadBMP("images/sun.bmp");		texturaSol = loadTexture(sol);		delete sol;
	Image* mercurio = loadBMP("images/mercury.bmp");	texturaMercurio = loadTexture(mercurio);		delete mercurio;
	Image* venus = loadBMP("images/venus.bmp");		texturaVenus = loadTexture(venus);		delete venus;
	Image* tierra = loadBMP("images/earth.bmp");		texturaTierra = loadTexture(tierra);		delete tierra;
	Image* marte = loadBMP("images/mars.bmp");		texturaMarte = loadTexture(marte);		delete marte;
	Image* jupiter = loadBMP("images/jupiter.bmp");	texturaJupiter = loadTexture(jupiter);		delete jupiter;
	Image* saturno = loadBMP("images/saturn.bmp");		texturaSaturno = loadTexture(saturno);		delete saturno;
	Image* urano = loadBMP("images/uranus.bmp");		texturaUrano = loadTexture(urano);		delete urano;
	Image* neptuno = loadBMP("images/neptune.bmp");	texturaNeptuno = loadTexture(neptuno);		delete neptuno;
	Image* pluton = loadBMP("images/pluto.bmp");		texturaPluton = loadTexture(pluton);		delete pluton;
	Image* log = loadBMP("images/logo.bmp");		logTexture = loadTexture(log);		delete log;

	//LIGHTING SETUP
	glEnable(GL_LIGHTING);
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
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

void orbitalTrails(void){
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

void drawlogoEscenario(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, logTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-100, -100, -100);
	glTexCoord2f(1.0, 0.0); glVertex3f(100, -100, -100);
	glTexCoord2f(1.0, 1.0); glVertex3f(100, 100, -100);
	glTexCoord2f(0.0, 1.0); glVertex3f(-100, 100, -100);
	glEnd();

	glutSwapBuffers();
}

void drawScene(void){
	cuadrosPorSegundo++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (cambiarCamara == 0)gluLookAt(0.0, zoom, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (cambiarCamara == 1)gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (cambiarCamara == 2)gluLookAt(0.0, zoom, 0.00001, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	if (orbitasGrandesActivas == 1) orbitalTrails();

	GLUquadric *cuadrica;
	cuadrica = gluNewQuadric();

	//Sol
	glPushMatrix();
	glRotatef(sol.orbita, 0.0, 1.0, 0.0);
	glTranslatef(sol.distancia, 0.0, 0.0);
	if (activarLeyenda == 1){
		glRasterPos3f(-1.2, 7.0, 0.0);
		glColor3ub(255, 255, 255);
		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sol");
	}
	glPushMatrix();
	glRotatef(sol.ejeInclinacion, 1.0, 0.0, 0.0);
	glRotatef(sol.ejeAnimacion, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaSol);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(cuadrica, 1);
	gluSphere(cuadrica, sol.radio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	//Mercury
	glPushMatrix();
	glRotatef(mercurio.orbita, 0.0, 1.0, 0.0);
	glTranslatef(mercurio.distancia, 0.0, 0.0);
	if (activarLeyenda == 1){
		glRasterPos3f(0.0, 3, 0.0);
		glColor3ub(255, 255, 255);
		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Mercury");
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
	if (activarLeyenda == 1){
		glRasterPos3f(0.0, 3, 0.0);
		glColor3ub(255, 255, 255);
		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Venus");
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

	//Earth, orbita, Moon
	glPushMatrix();
	glRotatef(tierra.orbita, 0.0, 1.0, 0.0);
	glTranslatef(tierra.distancia, 0.0, 0.0);
	if (activarLeyenda == 1){
		glRasterPos3f(0.0, 3, 0.0);
		glColor3ub(255, 255, 255);
		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Earth");
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
	if (pequenasOrbitasActivas == 1){
		luna.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1){
		luna.dibujarLuna();
	}
	glPopMatrix();

	//Mars, Orbits, Moons
	glPushMatrix();
	glRotatef(marte.orbita, 0.0, 1.0, 0.0);
	glTranslatef(marte.distancia, 0.0, 0.0);
	if (activarLeyenda == 1){
		glRasterPos3f(0.0, 3, 0.0);
		glColor3ub(255, 255, 255);
		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Mars");
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
	if (pequenasOrbitasActivas == 1){
		fobos.dibujarOrbitaPequeña();
		deimos.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1){
		fobos.dibujarLuna();
		deimos.dibujarLuna();
	}
	glPopMatrix();

	//Jupiter, Orbits, Moons
	glPushMatrix();
	glRotatef(jupiter.orbita, 0.0, 1.0, 0.0);
	glTranslatef(jupiter.distancia, 0.0, 0.0);
	if (activarLeyenda == 1){
		glRasterPos3f(0.0, 4.4, 0.0);
		glColor3ub(255, 255, 255);
		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Jupiter");
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
	if (pequenasOrbitasActivas == 1){
		io.dibujarOrbitaPequeña();
		europa.dibujarOrbitaPequeña();
		ganimides.dibujarOrbitaPequeña();
		calisto.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1){
		io.dibujarLuna();
		europa.dibujarLuna();
		ganimides.dibujarLuna();
		calisto.dibujarLuna();
	}
	glPopMatrix();

	//Saturn, orbita, Moon
	glPushMatrix();
	glRotatef(saturno.orbita, 0.0, 1.0, 0.0);
	glTranslatef(saturno.distancia, 0.0, 0.0);
	if (activarLeyenda == 1){
		glRasterPos3f(0.0, 4.4, 0.0);
		glColor3ub(255, 255, 255);
		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Saturn");
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
	if (pequenasOrbitasActivas == 1){
		tit.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1){
		tit.dibujarLuna();
	}
	glPopMatrix();

	glColor3ub(255, 255, 255);		//FIXES SHADING ISSUE

	//Uranus, orbita, Moon
	glPushMatrix();
	glRotatef(urano.orbita, 0.0, 1.0, 0.0);
	glTranslatef(urano.distancia, 0.0, 0.0);
	if (activarLeyenda == 1){
		glRasterPos3f(0.0, 4.4, 0.0);
		glColor3ub(255, 255, 255);
		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Uranus");
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
	if (pequenasOrbitasActivas == 1){
		puc.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1){
		puc.dibujarLuna();
	}
	glPopMatrix();

	//Neptune, orbita, Moon
	glPushMatrix();
	glRotatef(neptuno.orbita, 0.0, 1.0, 0.0);
	glTranslatef(neptuno.distancia, 0.0, 0.0);
	if (activarLeyenda == 1){
		glRasterPos3f(0.0, 4.4, 0.0);
		glColor3ub(255, 255, 255);
		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Neptune");
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
	if (pequenasOrbitasActivas == 1){
		tri.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1){
		tri.dibujarLuna();
	}
	glPopMatrix();

	//Pluto, orbita, Moon
	glPushMatrix();
	glRotatef(pluton.orbita, 0.0, 1.0, 0.0);
	glTranslatef(pluton.distancia, 0.0, 0.0);
	if (activarLeyenda == 1){
		glRasterPos3f(0.0, 3.0, 0.0);
		glColor3ub(255, 255, 255);
		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Pluto");
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
	if (pequenasOrbitasActivas == 1){
		nix.dibujarOrbitaPequeña();
	}
	if (activarLunas == 1){
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

	glutSwapBuffers();
}

void drawScenesInOrder(void){
	if (logoEscenario == 1){
		drawlogoEscenario();
	}
	else {
		drawScene();
	}
}

void resize(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

void animate(int n){
	if (animacionActiva){
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
		if (mercurio, venus, tierra, marte, jupiter, saturno, urano, neptuno, pluton, luna, fobos, deimos, io, europa, ganimides, calisto, tit, nix, puc, tri.orbita > 360.0){
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
		if (mercurio, venus, tierra, marte, jupiter, saturno, urano, neptuno, pluton.ejeAnimacion > 360.0){
			mercurio, venus, tierra, marte, jupiter, saturno, urano, neptuno, pluton.ejeAnimacion -= 360.0;
		}
		glutPostRedisplay();
		glutTimerFunc(30, animate, 1);
	}
}

void mouseControl(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		if (logoEscenario) logoEscenario = 0;

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(0);
	glutPostRedisplay();
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	if (direction > 0 && zoom < 100) zoom++;
	if (direction < 0 && zoom > -75) zoom--;
	glutPostRedisplay();
}

void keyInput(unsigned char key, int x, int y){
	switch (key){
	case 27: exit(0); break;
	case ' ': if (animacionActiva) animacionActiva = 0; else{ animacionActiva = 1; animate(1); } break;
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

void intructions(void){
	cout << "SPACE to play/pause the simulation." << endl;
	cout << "ESC to exit the simulation." << endl;
	cout << "O to show/hide Big Orbital Trails." << endl;
	cout << "o to show/hide Small Orbital Trails." << endl;
	cout << "M/m to show/hide Moons." << endl;
	cout << "L/l to show/hide labels" << endl;
	cout << "1, 2 and 3 to change camera angles." << endl;
	cout << "Scroll to change camera movement" << endl;
}

int main(int argc, char **argv){
	intructions();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("Solar System");
	glutDisplayFunc(drawScenesInOrder);
	glutReshapeFunc(resize);
	glutMouseFunc(mouseControl);
	glutKeyboardFunc(keyInput);
	glutMouseWheelFunc(mouseWheel);
	glewExperimental = GL_TRUE;
	glewInit();

	setup();
	glutMainLoop();
}