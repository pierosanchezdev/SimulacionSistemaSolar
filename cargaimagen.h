#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED

/**
 * Clase para representar una imagen.
 */
class Imagen {
public:
    /**
     * Constructor de la clase Imagen.
     * @param ps Puntero a los datos de los píxeles de la imagen.
     * @param w Ancho de la imagen.
     * @param h Altura de la imagen.
     */
    Imagen(char* ps, int w, int h);

    /**
     * Destructor de la clase Imagen.
     * Libera la memoria asignada a los datos de los píxeles.
     */
    ~Imagen();

    char* pixeles; ///< Arreglo de bytes que representa los píxeles de la imagen.
    int anchura;   ///< Ancho de la imagen.
    int altura;    ///< Altura de la imagen.
};

/**
 * Función para cargar una imagen BMP desde un archivo.
 * @param filename Ruta del archivo BMP.
 * @return Puntero a una instancia de la clase Imagen.
 */
Imagen* cargarBMP(const char* filename);

#endif
