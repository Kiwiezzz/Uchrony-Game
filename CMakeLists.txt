cmake_minimum_required(VERSION 3.10)

# Define el nombre de vuestro proyecto
project(UchronyGame LANGUAGES CXX)

# Busca la librería SFML
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

# Define el ejecutable del juego
add_executable(UchronyGame_Executable
    src/main.cpp
)

# Agregar directorio de headers
target_include_directories(UchronyGame_Executable PRIVATE Include)

# Enlaza las librerías al ejecutable del juego
target_link_libraries(UchronyGame_Executable
    PRIVATE
    sfml-system  
    sfml-window   
    sfml-graphics
)

# Establece el estándar de C++ (si usan C++17 o superior)
target_compile_features(UchronyGame_Executable PUBLIC cxx_std_17)