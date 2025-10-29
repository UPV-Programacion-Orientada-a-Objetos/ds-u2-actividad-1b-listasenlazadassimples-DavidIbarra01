//(Implementación del Serial)

#include "Serial.h"
#include <iostream>
#include <cstring> // Para memset

Serial::Serial() : fd(-1) {}

Serial::~Serial() {
    if (fd != -1) {
        cerrar();
    }
}

void Serial::cerrar() {
    close(fd);
    fd = -1;
}

bool Serial::abrir(const char* puerto, int baudrate) {
    // Abrir el puerto
    // O_RDWR = Leer y Escribir
    // O_NOCTTY = No convertirlo en la terminal de control del proceso
    fd = open(puerto, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        std::cerr << "Error [Serial] al abrir " << puerto << std::endl;
        return false;
    }

    // Obtener la configuración actual del puerto
    if (tcgetattr(fd, &tty) != 0) {
        std::cerr << "Error [Serial] al obtener atributos" << std::endl;
        return false;
    }

    //Configurar el puerto ---
    // Limpiar la estructura
    memset(&tty, 0, sizeof(tty));

    // Configuración de Baudrate (velocidad)
    speed_t speed;
    switch (baudrate) {
        case 9600: speed = B9600; break;
        case 115200: speed = B115200; break;
        default: speed = B9600;
    }
    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    // Configuración estándar (8N1 - 8 bits, sin paridad, 1 stop bit)
    tty.c_cflag &= ~PARENB; // Sin paridad
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8; // 8 bits

    // Modo "Raw" (no canónico) - procesamos los bytes tal como llegan
    tty.c_lflag &= ~ICANON; // Desactiva modo canónico (esperar \n)
    tty.c_lflag &= ~ECHO;   // No hacer eco
    tty.c_lflag &= ~ISIG;   // No interpretar señales
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Desactiva control de flujo
    tty.c_oflag &= ~OPOST; // Desactiva post-procesamiento

    // Tiempos de espera (Timeouts)
    tty.c_cc[VMIN] = 1;  // Bloquear hasta que 1 byte esté disponible
    tty.c_cc[VTIME] = 5; // Timeout de 0.5 segundos

    // Aplicar la configuración
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "Error [Serial] al aplicar atributos" << std::endl;
        return false;
    }

    return true;
}

int Serial::leerLinea(char* buffer, int tamBuffer) {
    char c = '\0';
    int i = 0;
    while (i < tamBuffer - 1) {
        int n = read(fd, &c, 1); // Lee 1 byte
        if (n > 0) {
            if (c == '\n' || c == '\r') {
                if (i > 0) break; // Termina si ya tenemos datos
            } else {
                buffer[i] = c;
                i++;
            }
        }
        // Si n <= 0, es un timeout o error, reintentamos
    }
    buffer[i] = '\0'; // Terminar el C-string
    return i;
}