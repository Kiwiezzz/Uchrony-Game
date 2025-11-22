cmake_minimum_required(VERSION 3.10)

# Define el nombre de vuestro proyecto
project(UchronyGame LANGUAGES CXX)

# Busca la librería SFML
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

# Lo que hace GLOB_RECURSE es buscar en todas las subcarpetas de un directorio archivos de un tipo
file(GLOB_RECURSE SOURCE "src/*.cpp")
# Y Los guarda en SOURCE en este caso

# Define el ejecutable del juego
add_executable(UchronyGame_Executable ${SOURCE})

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