//(El Gestor Principal)

#ifndef SISTEMA_H
#define SISTEMA_H

#include "Sensor.h" 
// Sensor.h ya incluye ListaSensor.h

class Sistema {
private:
    // La "Lista de Gestión Polimórfica"
    // Usamos nuestra propia lista genérica para almacenar punteros a la base
    ListaSensor<SensorBase*> listaGestion;

public:
    Sistema();
    ~Sistema();

    void agregarSensor(SensorBase* sensor);
    
    // Busca un sensor por su 'nombre'
    SensorBase* buscarSensor(const char* nombre);

    // Itera y ejecuta el procesamiento polimórfico
    void procesarTodos();
};

#endif