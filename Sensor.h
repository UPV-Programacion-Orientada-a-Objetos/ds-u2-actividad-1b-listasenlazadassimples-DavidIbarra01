/**
 * @file Sensor.h
 * @brief Define la jerarquía de clases polimórficas para los Sensores.
 * @details Contiene la clase base abstracta SensorBase y sus
 * clases derivadas (SensorTemperatura, SensorPresion).
 */
#ifndef SENSOR_H
#define SENSOR_H

#include "ListaSensor.h"
#include "Serial.h"
#include <iostream>

/**
 * @class SensorBase
 * @brief Clase Base Abstracta para todos los sensores del sistema.
 * @details Define la interfaz común que todos los sensores deben implementar,
 * forzando el polimorfismo a través de métodos virtuales puros.
 */
class SensorBase {
protected:
    /// @brief Identificador del sensor (ej. "T-001", "P-105").
    char nombre[50];

public:
    /**
     * @brief Constructor de SensorBase.
     * @param n El nombre (ID) para este sensor.
     */
    SensorBase(const char* n);
    
    /**
     * @brief Destructor Virtual (Crítico para polimorfismo).
     * @details Esencial para asegurar la correcta liberación de memoria
     * en la jerarquía polimórfica. Garantiza que se llame al destructor
     * de la clase derivada (ej. ~SensorTemperatura) cuando se hace delete
     * a un puntero SensorBase*.
     */
    virtual ~SensorBase();

    // --- Métodos Virtuales Puros ---
    
    /**
     * @brief Método virtual puro para procesar las lecturas almacenadas.
     * @details Cada clase derivada debe implementar su propia lógica
     * (ej. calcular promedio, encontrar mínimo, etc.).
     */
    virtual void procesarLectura() = 0;
    
    /**
     * @brief Método virtual puro para imprimir información del sensor.
     * @details Define la firma para un método de impresión de información.
     */
    virtual void imprimirInfo() const = 0;

    /**
     * @brief Método virtual puro para registrar una nueva lectura.
     * @details Define la interfaz para que cada sensor espere y
     * procese su tipo de dato específico desde el puerto serial.
     * @param port Referencia al objeto Serial desde donde se leerá.
     */
    virtual void registrarNuevaLectura(Serial& port) = 0;

    /**
     * @brief Obtiene el nombre (ID) del sensor.
     * @return Un puntero constante al C-string del nombre.
     */
    const char* getNombre() const;
};


/**
 * @class SensorTemperatura
 * @brief Clase derivada que maneja lecturas de temperatura (float).
 * @details Contiene una ListaSensor interna para almacenar valores float.
 */
class SensorTemperatura : public SensorBase {
private:
    /// @brief Lista enlazada interna para el historial de lecturas (float).
    ListaSensor<float> historial;

public:
    /**
     * @brief Constructor de SensorTemperatura.
     * @param n El nombre (ID) para este sensor.
     */
    SensorTemperatura(const char* n);
    
    /**
     * @brief Destructor de SensorTemperatura.
     * @details Imprime un log y libera automáticamente su 'historial' (ListaSensor<float>).
     */
    ~SensorTemperatura();

    /**
     * @brief Implementación del procesamiento para SensorTemperatura.
     * @details Calcula y elimina el valor más bajo de su lista interna.
     */
    void procesarLectura() override;
    
    /**
     * @brief Implementación de la impresión de info para SensorTemperatura.
     */
    void imprimirInfo() const override;
    
    /**
     * @brief Implementación del registro para SensorTemperatura.
     * @details Espera activamente una línea del puerto serial que comience con "T:".
     * @param port Referencia al objeto Serial.
     */
    void registrarNuevaLectura(Serial& port) override;
};


/**
 * @class SensorPresion
 * @brief Clase derivada que maneja lecturas de presión (int).
 * @details Contiene una ListaSensor interna para almacenar valores int.
 */
class SensorPresion : public SensorBase {
private:
    /// @brief Lista enlazada interna para el historial de lecturas (int).
    ListaSensor<int> historial;

public:
    /**
     * @brief Constructor de SensorPresion.
     * @param n El nombre (ID) para este sensor.
     */
    SensorPresion(const char* n);
    
    /**
     * @brief Destructor de SensorPresion.
     * @details Imprime un log y libera automáticamente su 'historial' (ListaSensor<int>).
     */
    ~SensorPresion();

    /**
     * @brief Implementación del procesamiento para SensorPresion.
     * @details Calcula el promedio de todas sus lecturas.
     */
    void procesarLectura() override;
    
    /**
     * @brief Implementación de la impresión de info para SensorPresion.
     */
    void imprimirInfo() const override;
    
    /**
     * @brief Implementación del registro para SensorPresion.
     * @details Espera activamente una línea del puerto serial que comience con "P:".
     * @param port Referencia al objeto Serial.
     */
    void registrarNuevaLectura(Serial& port) override;
};

#endif