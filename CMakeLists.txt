cmake_minimum_required(VERSION 3.10)
project(MonitorIC CXX)

# Usamos el estándar C++11 (o 14, 17)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Agregamos nuestro ejecutable y los archivos .cpp que necesita
add_executable(monitor
    main.cpp
    Serial.cpp
    Sensor.cpp
    Sistema.cpp
)

# En Linux, la comunicación serial puede requerir la librería 'pthread'
target_link_libraries(monitor PRIVATE pthread)