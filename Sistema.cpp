//(Implementación del Gestor)

#include "Sistema.h"
#include <cstring> // Para strcmp

Sistema::Sistema() {}

Sistema::~Sistema() {
    std::cout << "--- Liberacion de Memoria en Cascada ---" << std::endl;
    // Iteramos la lista de gestión
    Nodo<SensorBase*>* actual = listaGestion.getCabeza();
    while (actual != nullptr) {
        std::cout << "[Destructor General] Liberando Nodo: " << actual->dato->getNombre() << "." << std::endl;
        
        // 1. Liberamos el objeto Sensor (SensorTemperatura o SensorPresion)
        // Gracias al destructor VIRTUAL, se llama al destructor correcto.
        delete actual->dato; 
        
        // 2. El destructor de ListaSensor<SensorBase*> (que se llama solo)
        // se encargará de liberar el 'Nodo' en sí.
        
        actual = actual->siguiente;
    }
    // El destructor de 'listaGestion' se llama al final, limpiando los Nodos
    // (pero no los datos a los que apuntaban, por eso el 'delete' de arriba es vital)
}

void Sistema::agregarSensor(SensorBase* sensor) {
    listaGestion.insertarAlFinal(sensor);
}

SensorBase* Sistema::buscarSensor(const char* nombre) {
    Nodo<SensorBase*>* actual = listaGestion.getCabeza();
    while (actual != nullptr) {
        // Comparamos C-strings
        if (strcmp(actual->dato->getNombre(), nombre) == 0) {
            return actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr; // No encontrado
}

void Sistema::procesarTodos() {
    std::cout << "\n--- Ejecutando Polimorfismo ---" << std::endl;
    Nodo<SensorBase*>* actual = listaGestion.getCabeza();
    while (actual != nullptr) {
        std::cout << "-> Procesando Sensor " << actual->dato->getNombre() << "..." << std::endl;
        
        // ¡La magia del polimorfismo!
        // Llama a SensorTemperatura::procesarLectura() o 
        // SensorPresion::procesarLectura() según corresponda.
        actual->dato->procesarLectura();
        
        actual = actual->siguiente;
    }
}