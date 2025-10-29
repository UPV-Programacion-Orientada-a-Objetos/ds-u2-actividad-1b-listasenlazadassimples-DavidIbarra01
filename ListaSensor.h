#ifndef LISTASENSOR_H
#define LISTASENSOR_H

#include <iostream> // Solo para logs de liberación de memoria

// --- Definición del Nodo Genérico ---
template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    // Constructor del Nodo
    Nodo(T d) : dato(d), siguiente(nullptr) {}
};

// --- Definición de la Lista Enlazada Genérica ---
template <typename T>
class ListaSensor {
private:
    Nodo<T>* cabeza;
    int tamano;

    // Función de utilidad para copiar otra lista (para C. Copia y Op. Asignación)
    void copiarDesde(const ListaSensor<T>& otra) {
        cabeza = nullptr;
        tamano = 0;
        Nodo<T>* actualOtra = otra.cabeza;
        while (actualOtra != nullptr) {
            insertarAlFinal(actualOtra->dato);
            actualOtra = actualOtra->siguiente;
        }
    }

    // Función de utilidad para limpiar la lista
    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* aBorrar = actual;
            actual = actual->siguiente;
            
            // Log de liberación (como en el ejemplo de salida)
            // std::cout << "    [Log] Nodo<T> " << aBorrar->dato << " liberado." << std::endl;
            
            delete aBorrar;
        }
        cabeza = nullptr;
        tamano = 0;
    }

public:
    // 1. Constructor
    ListaSensor() : cabeza(nullptr), tamano(0) {}

    // 2. Destructor (Regla de los Tres)
    ~ListaSensor() {
        limpiar();
    }

    // 3. Constructor de Copia (Regla de los Tres)
    ListaSensor(const ListaSensor<T>& otra) {
        copiarDesde(otra);
    }

    // 4. Operador de Asignación (Regla de los Tres)
    ListaSensor<T>& operator=(const ListaSensor<T>& otra) {
        if (this != &otra) { // Evitar auto-asignación
            limpiar();
            copiarDesde(otra);
        }
        return *this;
    }

    // --- Métodos de la Lista ---

    void insertarAlFinal(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        tamano++;
    }

    // Método para eliminar un nodo por su valor (necesario para SensorTemperatura)
    void eliminarValor(T valor) {
        Nodo<T>* actual = cabeza;
        Nodo<T>* anterior = nullptr;

        while (actual != nullptr && actual->dato != valor) {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (actual == nullptr) return; // No encontrado

        if (anterior == nullptr) { // Es la cabeza
            cabeza = actual->siguiente;
        } else { // Es un nodo intermedio
            anterior->siguiente = actual->siguiente;
        }

        // std::cout << "    [Log] Nodo<T> " << actual->dato << " eliminado." << std::endl;
        delete actual;
        tamano--;
    }

    // Getters para iterar desde fuera
    Nodo<T>* getCabeza() const { return cabeza; }
    int getTamano() const { return tamano; }
};

#endif