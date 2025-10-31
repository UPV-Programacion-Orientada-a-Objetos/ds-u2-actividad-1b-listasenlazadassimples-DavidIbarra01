/**
 * @file ListaSensor.h
 * @brief Define la clase genérica ListaSensor y su struct anidado Nodo.
 */
#ifndef LISTASENSOR_H
#define LISTASENSOR_H

#include <iostream> // Solo para logs de liberación de memoria

/**
 * @struct Nodo
 * @brief Estructura genérica de un nodo para la ListaSensor.
 * @tparam T El tipo de dato que almacenará el nodo.
 */
template <typename T>
struct Nodo {
    /// @brief El dato almacenado en el nodo.
    T dato;
    /// @brief Puntero al siguiente nodo en la lista.
    Nodo<T>* siguiente;

    /**
     * @brief Constructor del Nodo.
     * @param d El dato de tipo T para inicializar el nodo.
     */
    Nodo(T d) : dato(d), siguiente(nullptr) {}
};

/**
 * @class ListaSensor
 * @brief Implementa una Lista Enlazada Simple Genérica.
 * @details Esta clase gestiona la memoria (nodos) de forma manual y cumple
 * con la Regla de los Tres para un manejo seguro de punteros y memoria dinámica.
 * @tparam T El tipo de dato que almacenará la lista (ej. int, float, SensorBase*).
 */
template <typename T>
class ListaSensor {
private:
    /// @brief Puntero al primer nodo (cabeza) de la lista.
    Nodo<T>* cabeza;
    /// @brief Contador del número de elementos en la lista.
    int tamano;

    /**
     * @brief Función de utilidad para copiar los nodos de otra lista.
     * @details Usada por el constructor de copia y el operador de asignación.
     * @param otra La lista (constante) desde la cual se copiarán los datos.
     */
    void copiarDesde(const ListaSensor<T>& otra) {
        cabeza = nullptr;
        tamano = 0;
        Nodo<T>* actualOtra = otra.cabeza;
        while (actualOtra != nullptr) {
            insertarAlFinal(actualOtra->dato);
            actualOtra = actualOtra->siguiente;
        }
    }

    /**
     * @brief Función de utilidad para limpiar la lista, liberando toda la memoria.
     * @details Usada por el destructor y el operador de asignación.
     */
    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* aBorrar = actual;
            actual = actual->siguiente;
            delete aBorrar;
        }
        cabeza = nullptr;
        tamano = 0;
    }

public:
    /**
     * @brief Constructor por defecto.
     * @details Inicializa una lista vacía.
     */
    ListaSensor() : cabeza(nullptr), tamano(0) {}

    /**
     * @brief Destructor (Regla de los Tres).
     * @details Llama a limpiar() para liberar todos los nodos.
     */
    ~ListaSensor() {
        limpiar();
    }

    /**
     * @brief Constructor de Copia (Regla de los Tres).
     * @param otra La lista a copiar.
     */
    ListaSensor(const ListaSensor<T>& otra) {
        copiarDesde(otra);
    }

    /**
     * @brief Operador de Asignación (Regla de los Tres).
     * @details Previene la auto-asignación, limpia la lista actual y copia desde la otra.
     * @param otra La lista a asignar.
     * @return Referencia a `*this`.
     */
    ListaSensor<T>& operator=(const ListaSensor<T>& otra) {
        if (this != &otra) { // Evitar auto-asignación
            limpiar();
            copiarDesde(otra);
        }
        return *this;
    }

    // --- Métodos de la Lista ---

    /**
     * @brief Inserta un nuevo dato al final de la lista.
     * @details Crea un nuevo nodo y lo enlaza al final.
     * @param dato El valor de tipo T que se agregará.
     */
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

    /**
     * @brief Elimina la primera ocurrencia de un nodo por su valor.
     * @details Busca un valor y, si lo encuentra, elimina el nodo y re-enlaza la lista.
     * @param valor El valor de tipo T a buscar y eliminar.
     */
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

        delete actual;
        tamano--;
    }

    /**
     * @brief Obtiene el puntero a la cabeza de la lista.
     * @return Puntero constante al primer nodo (Nodo<T>*).
     */
    Nodo<T>* getCabeza() const { return cabeza; }
    
    /**
     * @brief Obtiene el tamaño actual de la lista.
     * @return El número de elementos (int).
     */
    int getTamano() const { return tamano; }
};

#endif