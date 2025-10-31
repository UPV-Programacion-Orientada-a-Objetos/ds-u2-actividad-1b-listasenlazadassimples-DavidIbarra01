/**
 * @file Sistema.h
 * @brief Define la clase Sistema, gestora principal del programa.
 */
#ifndef SISTEMA_H
#define SISTEMA_H

#include "Sensor.h" 
// Sensor.h ya incluye ListaSensor.h

/**
 * @class Sistema
 * @brief Clase principal que gestiona la lista polimórfica de sensores.
 * @details Contiene la lista de gestión principal que almacena punteros
 * SensorBase* y orquesta las operaciones principales.
 */
class Sistema {
private:
    /**
     * @brief La "Lista de Gestión Polimórfica".
     * @details Almacena punteros a SensorBase, permitiendo que
     * SensorTemperatura y SensorPresion coexistan en la misma lista.
     */
    ListaSensor<SensorBase*> listaGestion;

public:
    /**
     * @brief Constructor de Sistema.
     */
    Sistema();
    
    /**
     * @brief Destructor de Sistema.
     * @details Inicia la "Liberación de Memoria en Cascada". Itera sobre la
     * listaGestion y aplica `delete` a cada puntero `SensorBase*`.
     * Gracias al destructor virtual de SensorBase, esto llama al
     * destructor correcto (ej. ~SensorTemperatura), que a su vez libera
     * su lista interna.
     */
    ~Sistema();

    /**
     * @brief Agrega un nuevo sensor (ya creado) a la lista de gestión.
     * @param sensor Un puntero de tipo SensorBase* al objeto a agregar.
     */
    void agregarSensor(SensorBase* sensor);
    
    /**
     * @brief Busca un sensor en la lista de gestión por su nombre (ID).
     * @param nombre El C-string del ID del sensor a buscar.
     * @return Un puntero SensorBase* al sensor si se encuentra, o `nullptr` si no.
     */
    SensorBase* buscarSensor(const char* nombre);

    /**
     * @brief Ejecuta el procesamiento polimórfico.
     * @details Itera sobre la listaGestion y llama al método `procesarLectura()`
     * de cada sensor. El polimorfismo asegura que se ejecute la
     * implementación correcta (Temp o Presion).
     */
    void procesarTodos();
};

#endif