#ifndef PLANETA_H
#define PLANETA_H

#include <GL/glut.h>

/**
 * Clase que representa un planeta con propiedades como radio, distancia de su órbita,
 * inclinación de su eje y velocidad de órbita.
 */
class Planeta {
public:
    float radio;             ///< Radio del planeta.
    float distancia;         ///< Distancia desde su órbita al punto central.
    float orbita;            ///< Ángulo actual de la órbita.
    float velocidadOrbita;   ///< Velocidad de la órbita.
    float ejeInclinacion;    ///< Inclinación del eje del planeta.
    float ejeAnimacion;      ///< Ángulo de rotación del planeta sobre su eje.

    /**
     * Constructor de la clase Planeta.
     * @param _radio Radio del planeta.
     * @param _distancia Distancia de la órbita.
     * @param _orbita Ángulo inicial de la órbita.
     * @param _velocidadOrbita Velocidad de la órbita.
     * @param _ejeInclinacion Inclinación del eje del planeta.
     * @param _ejeAnimacion Ángulo inicial de rotación sobre su eje.
     */
    Planeta(float _radio, float _distancia, float _orbita, float _velocidadOrbita,
        float _ejeInclinacion, float _ejeAnimacion);

    /**
     * Dibuja una órbita pequeña para el planeta.
     */
    void dibujarOrbitaPequeña();

    /**
     * Dibuja el planeta (o luna) usando una esfera.
     */
    void dibujarLuna();
};

#endif // PLANETA_H
