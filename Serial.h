//(El Lector de Puerto Serial)

#ifndef SERIAL_H
#define SERIAL_H

// Librerías del sistema POSIX para el puerto serial
#include <fcntl.h>   // Contiene control de archivos (ej. O_RDWR)
#include <termios.h> // Contiene control de terminal POSIX
#include <unistd.h>  // Contiene llamadas al sistema (ej. read, write, close)

class Serial {
private:
    int fd; // File Descriptor (identificador del puerto)
    struct termios tty; // Estructura de configuración del puerto

public:
    Serial();
    ~Serial();

    // Abre y configura el puerto
    bool abrir(const char* puerto, int baudrate);
    
    // Cierra el puerto
    void cerrar();

    // Lee una línea completa (hasta '\n') del puerto serial
    // Guarda el resultado en 'buffer'
    // Retorna el número de bytes leídos
    int leerLinea(char* buffer, int tamBuffer);
};

#endif