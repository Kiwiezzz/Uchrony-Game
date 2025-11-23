cmake_minimum_required(VERSION 3.12)

project(UchronyGame LANGUAGES CXX)

option(USE_BUNDLED_SFML "Buscar SFML dentro de la carpeta ${CMAKE_SOURCE_DIR}/lib primero" ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(USE_BUNDLED_SFML)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib")
endif()

find_package(SFML 2.5 COMPONENTS system window graphics audio)

if(NOT SFML_FOUND)
    message(STATUS "SFML no encontrada automáticamente.")
    message(STATUS "Si has añadido SFML en 'lib/', asegúrate de que contiene el paquete CMake (por ejemplo 'lib/cmake/SFML').")
    message(STATUS "Opciones para resolver: instalar SFML en el sistema, o establecer -DSFML_DIR=/ruta/a/lib/cmake/SFML, o poner SFML en 'lib/'.")
    message(FATAL_ERROR "SFML no encontrada. Provee SFML o desactiva USE_BUNDLED_SFML si quieres usar la versión del sistema.")
endif()

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")

# Ejecutable
add_executable(UchronyGame_Executable ${SOURCE_FILES})
target_include_directories(UchronyGame_Executable PRIVATE Include)
target_compile_features(UchronyGame_Executable PUBLIC cxx_std_17)

if(TARGET SFML::System)
    target_link_libraries(UchronyGame_Executable PRIVATE SFML::System SFML::Window SFML::Graphics SFML::Audio)
else()
    target_link_libraries(UchronyGame_Executable PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
endif()

set_target_properties(UchronyGame_Executable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
)

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "SFML Found: ${SFML_FOUND}")
