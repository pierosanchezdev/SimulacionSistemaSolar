#include "Planeta.h"

/**
 * Constructor de la clase Planeta.
 */
Planeta::Planeta(float _radio, float _distancia, float _orbita, float _velocidadOrbita,
    float _ejeInclinacion, float _ejeAnimacion)
    : radio(_radio), distancia(_distancia), orbita(_orbita),
    velocidadOrbita(_velocidadOrbita), ejeInclinacion(_ejeInclinacion),
    ejeAnimacion(_ejeAnimacion) {}

/**
 * Dibuja una órbita pequeña representada como un toroide delgado.
 */
void Planeta::dibujarOrbitaPequeña() {
    glPushMatrix();
    glColor3ub(255, 255, 255);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glutWireTorus(0.001, distancia, 100.0, 100.0);
    glPopMatrix();
}

/**
 * Dibuja el planeta o luna como una esfera.
 */
void Planeta::dibujarLuna() {
    GLUquadricObj* cuadrica = gluNewQuadric();
    glPushMatrix();
    glColor3ub(255, 255, 255);
    glRotatef(orbita, 0.0, 1.0, 0.0);
    glTranslatef(distancia, 0.0, 0.0);
    gluSphere(cuadrica, radio, 20.0, 20.0);
    glPopMatrix();
}
