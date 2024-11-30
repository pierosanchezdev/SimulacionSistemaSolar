#ifndef PLANETA_H
#define PLANETA_H

#include <GL/glut.h>

/**
 * Clase que representa un planeta con propiedades como radio, distancia de su �rbita,
 * inclinaci�n de su eje y velocidad de �rbita.
 */
class Planeta {
public:
    float radio;             ///< Radio del planeta.
    float distancia;         ///< Distancia desde su �rbita al punto central.
    float orbita;            ///< �ngulo actual de la �rbita.
    float velocidadOrbita;   ///< Velocidad de la �rbita.
    float ejeInclinacion;    ///< Inclinaci�n del eje del planeta.
    float ejeAnimacion;      ///< �ngulo de rotaci�n del planeta sobre su eje.

    /**
     * Constructor de la clase Planeta.
     * @param _radio Radio del planeta.
     * @param _distancia Distancia de la �rbita.
     * @param _orbita �ngulo inicial de la �rbita.
     * @param _velocidadOrbita Velocidad de la �rbita.
     * @param _ejeInclinacion Inclinaci�n del eje del planeta.
     * @param _ejeAnimacion �ngulo inicial de rotaci�n sobre su eje.
     */
    Planeta(float _radio, float _distancia, float _orbita, float _velocidadOrbita,
        float _ejeInclinacion, float _ejeAnimacion);

    /**
     * Dibuja una �rbita peque�a para el planeta.
     */
    void dibujarOrbitaPeque�a();

    /**
     * Dibuja el planeta (o luna) usando una esfera.
     */
    void dibujarLuna();
};

#endif // PLANETA_H
