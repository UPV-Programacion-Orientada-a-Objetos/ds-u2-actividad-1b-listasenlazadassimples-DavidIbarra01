#include <iostream>
#include <limits> // Para limpiar el buffer de std::cin
#include "Sistema.h"
#include "Serial.h"

// --- Prototipos de funciones del menú ---
void mostrarMenu();
void crearSensor(Sistema& sistema, bool esTemp);
void registrarLectura(Sistema& sistema, Serial& port);

int main() {
    // --- Configuración del Puerto Serial ---
    Serial serial;
    // IMPORTANTE: Cambia "/dev/ttyUSB0" por tu puerto si es diferente (ej. /dev/ttyACM0)
    const char* puerto = "/dev/ttyUSB0"; 
    
    std::cout << "Intentando conectar a Arduino en " << puerto << "..." << std::endl;
    if (!serial.abrir(puerto, 9600)) {
        std::cerr << "Error: No se pudo conectar al Arduino." << std::endl;
        std::cerr << "Asegurate de: \n1. Que este conectado.\n2. Que el puerto sea correcto.\n3. Que tengas permisos (sudo usermod -a -G dialout $USER y REINICIA SESION)." << std::endl;
        return 1;
    }
    std::cout << "Conexion con Arduino exitosa." << std::endl;
    // Damos tiempo al Arduino para que se estabilice
    sleep(2); 

    // --- Inicio del Sistema ---
    Sistema sistema;
    int opcion = 0;
    
    std::cout << "\n--- Sistema IoT de Monitoreo Polimorfico ---" << std::endl;

    while (opcion != 5) {
        mostrarMenu();
        std::cin >> opcion;

        // Limpiar buffer de entrada por si el usuario introduce texto
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            opcion = 0; // Opción inválida
        }
        // Limpiar el '\n' restante
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        switch (opcion) {
            case 1:
                crearSensor(sistema, true); // true = Temperatura
                break;
            case 2:
                crearSensor(sistema, false); // false = Presion
                break;
            case 3:
                registrarLectura(sistema, serial);
                break;
            case 4:
                sistema.procesarTodos();
                break;
            case 5:
                std::cout << "\nOpcion 5: Cerrar Sistema (Liberar Memoria)" << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
                break;
        }
    }

    // Al salir del 'main', el destructor de 'sistema' se llama automáticamente,
    // iniciando la liberación en cascada.
    // El destructor de 'serial' también se llama, cerrando el puerto.
    std::cout << "Sistema cerrado. Memoria limpia." << std::endl;
    return 0;
}

// --- Implementación de funciones del menú ---

void mostrarMenu() {
    std::cout << "\n--- Menu Principal ---" << std::endl;
    std::cout << "1: Crear Sensor (Tipo Temp - FLOAT)" << std::endl;
    std::cout << "2: Crear Sensor (Tipo Presion - INT)" << std::endl;
    std::cout << "3: Registrar Lectura (Desde Arduino)" << std::endl;
    std::cout << "4: Ejecutar Procesamiento Polimorfico" << std::endl;
    std::cout << "5: Cerrar Sistema (Liberar Memoria)" << std::endl;
    std::cout << "Seleccione una opcion: ";
}

void crearSensor(Sistema& sistema, bool esTemp) {
    char nombre[50];
    if (esTemp) {
        std::cout << "Opcion 1: Crear Sensor (Tipo Temp - FLOAT)" << std::endl;
        std::cout << "Ingrese ID (ej. T-001): ";
    } else {
        std::cout << "Opcion 2: Crear Sensor (Tipo Presion - INT)" << std::endl;
        std::cout << "Ingrese ID (ej. P-105): ";
    }
    
    std::cin.getline(nombre, 50); // Leer C-string

    SensorBase* nuevoSensor = nullptr;
    if (esTemp) {
        nuevoSensor = new SensorTemperatura(nombre);
    } else {
        nuevoSensor = new SensorPresion(nombre);
    }
    
    sistema.agregarSensor(nuevoSensor);
    std::cout << "Sensor '" << nombre << "' creado e insertado en la lista de gestion." << std::endl;
}

void registrarLectura(Sistema& sistema, Serial& port) {
    char id[50];
    std::cout << "Opcion 3: Registrar Lectura" << std::endl;
    std::cout << "Ingrese ID del sensor para registrar lectura: ";
    std::cin.getline(id, 50);

    SensorBase* sensor = sistema.buscarSensor(id);

    if (sensor == nullptr) {
        std::cout << "Error: Sensor con ID '" << id << "' no encontrado." << std::endl;
    } else {
        // Polimorfismo: Llama al método 'registrarNuevaLectura'
        // apropiado (Temp o Presion).
        // Ese método se encargará de esperar el prefijo correcto (T: o P:)
        sensor->registrarNuevaLectura(port);
    }
}