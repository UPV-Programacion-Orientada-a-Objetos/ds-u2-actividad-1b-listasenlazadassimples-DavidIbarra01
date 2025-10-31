/**
 * @file Sensor.cpp
 * @brief Implementación de los métodos de SensorBase, SensorTemperatura y SensorPresion.
 */

#include "Sensor.h"
#include <cstring> // Para strcpy y strcmp
#include <cstdlib> // Para atof (string a float) y atoi (string a int)
#include <iostream>

// --- Implementación SensorBase ---
SensorBase::SensorBase(const char* n) {
    // Copia segura del nombre (evita desbordamiento)
    strncpy(nombre, n, 49);
    nombre[49] = '\0'; // Asegura terminación nula
}

SensorBase::~SensorBase() {
    // El destructor virtual es necesario, aunque esté vacío,
    // para asegurar que se llame al destructor de la clase derivada.
    // std::cout << "  [Destructor Base] Sensor " << nombre << " base." << std::endl;
}

const char* SensorBase::getNombre() const {
    return nombre;
}


// --- Implementación SensorTemperatura ---
SensorTemperatura::SensorTemperatura(const char* n) : SensorBase(n) {}

SensorTemperatura::~SensorTemperatura() {
    std::cout << "  [Destructor Sensor " << nombre << "] Liberando Lista Interna <float>..." << std::endl;
    // El destructor de 'historial' (ListaSensor<float>) se llama automáticamente aquí
    // y limpiará todos sus nodos gracias a la Regla de los Tres.
}

void SensorTemperatura::registrarNuevaLectura(Serial& port) {
    char buffer[100];
    std::cout << "Esperando lectura 'T:' desde Arduino..." << std::endl;

    while (true) {
        int bytes = port.leerLinea(buffer, 100);
        if (bytes > 0 && buffer[0] == 'T' && buffer[1] == ':') {
            // Encontramos una lectura de Temperatura
            // 'atof' convierte el C-string (desde el 3er char) a float
            float valor = atof(buffer + 2); 
            historial.insertarAlFinal(valor);
            std::cout << "[Log] Insertando Nodo<float> " << valor << " en " << nombre << "." << std::endl;
            break;
        }
        // Si no es 'T:', sigue leyendo hasta encontrarla
    }
}

void SensorTemperatura::procesarLectura() {
    Nodo<float>* actual = historial.getCabeza();
    if (actual == nullptr) {
        std::cout << "[" << nombre << "] (Temperatura): No hay lecturas para procesar." << std::endl;
        return;
    }

    // Lógica: Encontrar y eliminar la lectura más baja
    float minVal = actual->dato;
    float suma = 0;
    int n = historial.getTamano();

    while (actual != nullptr) {
        if (actual->dato < minVal) {
            minVal = actual->dato;
        }
        suma += actual->dato;
        actual = actual->siguiente;
    }

    historial.eliminarValor(minVal);
    float promedioRestante = (n > 1) ? (suma - minVal) / (n - 1) : 0;

    std::cout << "[" << nombre << "] (Temperatura): Lectura mas baja (" << minVal << ") eliminada. Promedio restante: " << promedioRestante << "." << std::endl;
}

void SensorTemperatura::imprimirInfo() const {
    // (Este método no se usa en el ejemplo, pero es requerido)
    std::cout << "Sensor [TEMP] " << nombre << std::endl;
}


// --- Implementación SensorPresion ---
SensorPresion::SensorPresion(const char* n) : SensorBase(n) {}

SensorPresion::~SensorPresion() {
    std::cout << "  [Destructor Sensor " << nombre << "] Liberando Lista Interna <int>..." << std::endl;
    // El destructor de 'historial' (ListaSensor<int>) se llama automáticamente.
}

void SensorPresion::registrarNuevaLectura(Serial& port) {
    char buffer[100];
    std::cout << "Esperando lectura 'P:' desde Arduino..." << std::endl;

    while (true) {
        int bytes = port.leerLinea(buffer, 100);
        if (bytes > 0 && buffer[0] == 'P' && buffer[1] == ':') {
            // Encontramos una lectura de Presión
            // 'atoi' convierte el C-string (desde el 3er char) a int
            int valor = atoi(buffer + 2);
            historial.insertarAlFinal(valor);
            std::cout << "[Log] Insertando Nodo<int> " << valor << " en " << nombre << "." << std::endl;
            break;
        }
        // Si no es 'P:', sigue leyendo
    }
}

void SensorPresion::procesarLectura() {
    Nodo<int>* actual = historial.getCabeza();
    int n = historial.getTamano();

    if (n == 0) {
        std::cout << "[" << nombre << "] (Presion): No hay lecturas para procesar." << std::endl;
        return;
    }

    // Lógica: Calcular el promedio
    float suma = 0;
    while (actual != nullptr) {
        suma += actual->dato;
        actual = actual->siguiente;
    }

    float promedio = suma / n;
    std::cout << "[" << nombre << "] (Presion): Promedio de " << n << " lecturas: " << promedio << "." << std::endl;
}

void SensorPresion::imprimirInfo() const {
    // (Este método no se usa en el ejemplo, pero es requerido)
    std::cout << "Sensor [PRESION] " << nombre << std::endl;
}