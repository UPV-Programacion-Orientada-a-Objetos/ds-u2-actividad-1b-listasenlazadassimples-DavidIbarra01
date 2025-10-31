/**
 * @file Serial.h
 * @brief Define la clase Serial para comunicación en sistemas POSIX (Linux/macOS).
 */
#ifndef SERIAL_H
#define SERIAL_H

// Librerías del sistema POSIX para el puerto serial
#include <fcntl.h>   // Contiene control de archivos (ej. O_RDWR)
#include <termios.h> // Contiene control de terminal POSIX
#include <unistd.h>  // Contiene llamadas al sistema (ej. read, write, close)

/**
 * @class Serial
 * @brief Abstrae la comunicación con el puerto serial (ej. Arduino).
 * @details Utiliza las APIs de bajo nivel de POSIX (termios.h, fcntl.h)
 * para configurar y leer desde un puerto serial.
 */
class Serial {
private:
    /// @brief File Descriptor (identificador de archivo) para el puerto serial.
    int fd;
    /// @brief Estructura termios que almacena la configuración del puerto.
    struct termios tty;

public:
    /**
     * @brief Constructor por defecto.
     * @details Inicializa el file descriptor a -1 (inválido).
     */
    Serial();
    
    /**
     * @brief Destructor.
     * @details Cierra automáticamente el puerto si está abierto.
     */
    ~Serial();

    /**
     * @brief Abre y configura el puerto serial.
     * @param puerto La ruta del dispositivo (ej. "/dev/ttyACM0").
     * @param baudrate La velocidad de comunicación (ej. 9600).
     * @return true si la apertura y configuración fueron exitosas, false en caso contrario.
     */
    bool abrir(const char* puerto, int baudrate);
    
    /**
     * @brief Cierra la conexión con el puerto serial.
     */
    void cerrar();

    /**
     * @brief Lee una línea completa (hasta '\n') del puerto serial.
     * @details Lee byte por byte hasta encontrar un salto de línea o llenar el buffer.
     * Es una lectura bloqueante con timeout.
     * @param buffer Puntero al buffer de char donde se guardará la línea.
     * @param tamBuffer El tamaño máximo del buffer.
     * @return El número de bytes leídos (excluyendo el '\0').
     */
    int leerLinea(char* buffer, int tamBuffer);
};

#endif