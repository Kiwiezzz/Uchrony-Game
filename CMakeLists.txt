cmake_minimum_required(VERSION 3.12)

# Proyecto
project(UchronyGame LANGUAGES CXX)

# Opciones
option(USE_BUNDLED_SFML "Buscar SFML dentro de la carpeta ${CMAKE_SOURCE_DIR}/lib primero" ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Si hay una copia de SFML incluida en `lib/`, añade esa ruta a las pistas de búsqueda
if(USE_BUNDLED_SFML)
    if(WIN32)
        list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib/SFML-2.6.2")
    endif()
endif()

# Intenta encontrar SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Recoger fuentes
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")

# EXCLUIR archivos que dependen de ImGui (temporalmente para que compile demo.cpp)
list(REMOVE_ITEM SOURCE_FILES 
    "${CMAKE_SOURCE_DIR}/src/DialogueManager.cpp"
    "${CMAKE_SOURCE_DIR}/src/DialogueUI.cpp"
    "${CMAKE_SOURCE_DIR}/src/MenuUI.cpp"
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/Game.cpp"
)

# Ejecutable
add_executable(UchronyGame_Executable ${SOURCE_FILES})
target_include_directories(UchronyGame_Executable PRIVATE Include)
target_compile_features(UchronyGame_Executable PUBLIC cxx_std_17)

# Vincula SFML
target_link_libraries(UchronyGame_Executable PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# Rutas de salida
set_target_properties(UchronyGame_Executable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
) 