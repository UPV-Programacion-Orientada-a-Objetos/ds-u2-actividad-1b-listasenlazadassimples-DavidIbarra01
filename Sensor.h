// (Jerarquía de Clases Polimórfica)

#ifndef SENSOR_H
#define SENSOR_H

#include "ListaSensor.h"
#include "Serial.h"
#include <iostream>

// Clase Base Abstracta ---
class SensorBase {
protected:
    char nombre[50];

public:
    // Constructor
    SensorBase(const char* n);
    
    // 1. Destructor Virtual (Crítico para polimorfismo)
    virtual ~SensorBase();

    //Métodos Virtuales Puros ---
    
    // 2. Procesa el historial de lecturas (lógica distinta)
    virtual void procesarLectura() = 0;
    
    // 3. Imprime la información del sensor
    virtual void imprimirInfo() const = 0;

    // 4. Espera y registra una nueva lectura desde el puerto serial
    virtual void registrarNuevaLectura(Serial& port) = 0;

    // Getter para buscar
    const char* getNombre() const;
};


//Clase Derivada: Temperatura (float) ---
class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> historial;

public:
    SensorTemperatura(const char* n);
    ~SensorTemperatura(); // Destructor

    // Implementación de métodos virtuales
    void procesarLectura() override;
    void imprimirInfo() const override;
    void registrarNuevaLectura(Serial& port) override;
};


//Clase Derivada: Presión (int) ---
class SensorPresion : public SensorBase {
private:
    ListaSensor<int> historial;

public:
    SensorPresion(const char* n);
    ~SensorPresion(); // Destructor

    // Implementación de métodos virtuales
    void procesarLectura() override;
    void imprimirInfo() const override;
    void registrarNuevaLectura(Serial& port) override;
};

#endif