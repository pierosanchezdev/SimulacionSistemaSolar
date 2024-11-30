#include <assert.h>
#include <fstream>
#include "cargaimagen.h"

using namespace std;

// Constructor de la clase Imagen
// Inicializa una instancia de Imagen con los píxeles, ancho y alto especificados.
Imagen::Imagen(char* ps, int w, int h) : pixeles(ps), anchura(w), altura(h) {}

// Destructor de la clase Imagen
// Libera la memoria asignada para los píxeles de la imagen.
Imagen::~Imagen() {
    delete[] pixeles;
}

namespace {
    // Convierte un arreglo de 4 bytes en un entero (little-endian a entero).
    int toInt(const char* bytes) {
        return (int)(((unsigned char)bytes[3] << 24) |
            ((unsigned char)bytes[2] << 16) |
            ((unsigned char)bytes[1] << 8) |
            (unsigned char)bytes[0]);
    }

    // Convierte un arreglo de 2 bytes en un entero corto (little-endian a short).
    short toShort(const char* bytes) {
        return (short)(((unsigned char)bytes[1] << 8) |
            (unsigned char)bytes[0]);
    }

    // Lee un entero de 4 bytes desde un flujo de entrada.
    int readInt(ifstream& input) {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

    // Lee un entero corto de 2 bytes desde un flujo de entrada.
    short readShort(ifstream& input) {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

    // Clase para manejar arreglos dinámicos de forma segura.
    template<class T>
    class auto_array {
    private:
        T* array;
        mutable bool isReleased;
    public:
        // Constructor para inicializar el arreglo.
        explicit auto_array(T* array_ = NULL) :
            array(array_), isReleased(false) {
        }

        // Constructor de copia que transfiere la propiedad del arreglo.
        auto_array(const auto_array<T>& aarray) {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        // Destructor que libera la memoria si no se ha liberado previamente.
        ~auto_array() {
            if (!isReleased && array != NULL) {
                delete[] array;
            }
        }

        // Devuelve el puntero al arreglo.
        T* get() const {
            return array;
        }

        // Sobrecarga del operador de acceso al contenido del arreglo.
        T& operator*() const {
            return *array;
        }

        // Sobrecarga del operador de asignación que transfiere la propiedad del arreglo.
        void operator=(const auto_array<T>& aarray) {
            if (!isReleased && array != NULL) {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        // Sobrecarga del operador para acceder a los elementos del arreglo.
        T* operator->() const {
            return array;
        }

        // Libera el control del arreglo sin liberarlo de la memoria.
        T* release() {
            isReleased = true;
            return array;
        }

        // Reinicia el arreglo con un nuevo puntero.
        void reset(T* array_ = NULL) {
            if (!isReleased && array != NULL) {
                delete[] array;
            }
            array = array_;
        }

        // Operadores de acceso y desplazamiento en el arreglo.
        T* operator+(int i) {
            return array + i;
        }

        T& operator[](int i) {
            return array[i];
        }
    };
}

// Carga una imagen BMP desde un archivo.
// Verifica el formato del archivo, extrae los datos de la imagen, y los reorganiza en formato RGB.
Imagen* cargarBMP(const char* nombreArchivo) {
    ifstream input;
    input.open(nombreArchivo, ifstream::binary);
    assert(!input.fail() || !"No se pudo encontrar el archivo");

    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"No es un archivo BMP válido");

    input.ignore(8); // Ignora los bytes no relevantes.
    int dataOffset = readInt(input); // Obtiene el offset donde comienzan los datos de la imagen.

    int headerSize = readInt(input);
    int anchura;
    int altura;

    // Verifica y maneja el tamaño del encabezado para determinar cómo leer la imagen.
    switch (headerSize) {
    case 40:
        anchura = readInt(input);
        altura = readInt(input);
        input.ignore(2); // Ignora el número de planos.
        assert(readShort(input) == 24 || !"La imagen no tiene 24 bits por píxel");
        assert(readShort(input) == 0 || !"La imagen está comprimida");
        break;
    case 12:
        anchura = readShort(input);
        altura = readShort(input);
        input.ignore(2); // Ignora el número de planos.
        assert(readShort(input) == 24 || !"La imagen no tiene 24 bits por píxel");
        break;
    default:
        assert(!"Formato BMP desconocido");
    }

    // Calcula los bytes por fila y lee los datos de píxeles.
    int bytesPerRow = ((anchura * 3 + 3) / 4) * 4 - (anchura * 3 % 4);
    int size = bytesPerRow * altura;
    auto_array<char> pixeles(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixeles.get(), size);

    // Reorganiza los datos de píxeles para ajustarse al formato RGB.
    auto_array<char> pixels2(new char[anchura * altura * 3]);
    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < anchura; x++) {
            for (int c = 0; c < 3; c++) {
                pixels2[3 * (anchura * y + x) + c] =
                    pixeles[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Imagen(pixels2.release(), anchura, altura);
}
