cmake_minimum_required(VERSION 3.10)

# Define el nombre de vuestro proyecto
project(UchronyGame LANGUAGES CXX)

# Busca la librería SFML
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

# Define el ejecutable del juego
add_executable(UchronyGame_Executable
    src/demo.cpp
    src/Entities/Player.cpp     # <--- AÑADIDO
    src/Utils/NavGrid.cpp     # <--- AÑADIDO
    src/Utils/Pathfinder.cpp  # <--- AÑADIDO
    src/Utils/Collision.cpp   # <--- AÑADIDO
    src/Entities/Inventory.cpp # <--- Añadido: implementación del inventario UI
    src/Entities/Item.cpp
    # ... Cualquier otro cpp
)

# Agregar directorio de headers (Esto ya estaba bien)
target_include_directories(UchronyGame_Executable PRIVATE Include) 

# Enlaza las librerías al ejecutable del juego
target_link_libraries(UchronyGame_Executable
    PRIVATE
    sfml-system  
    sfml-window   
    sfml-graphics
    sfml-audio
)

# Establece el estándar de C++ (Esto ya estaba bien)
target_compile_features(UchronyGame_Executable PUBLIC cxx_std_17) 