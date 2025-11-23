cmake_minimum_required(VERSION 3.12)

# Proyecto
project(UchronyGame LANGUAGES CXX)

# Opciones
option(USE_BUNDLED_SFML "Buscar SFML dentro de la carpeta ${CMAKE_SOURCE_DIR}/lib primero" ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Si hay una copia de SFML incluida en `lib/`, añade esa ruta a las pistas de búsqueda
# Solo usamos la SFML empaquetada en lib/ en Windows (evita enlazar librerías Windows en Linux)
if(USE_BUNDLED_SFML)
    if(WIN32)
        list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib")
    else()
        message(STATUS "USE_BUNDLED_SFML=ON, pero no se usará la SFML incluida en 'lib/' en este sistema (no-Windows).")
    endif()
endif()

# Intenta encontrar SFML (usa HINTS a la carpeta lib/ para builds incluidas)
find_package(SFML 2.5 COMPONENTS system window graphics audio)

if(NOT SFML_FOUND)
    message(STATUS "SFML no encontrada automáticamente.")
    message(STATUS "Si estás en Linux instala libsfml-dev (ej. 'sudo apt install libsfml-dev') o proporciona SFML con -DSFML_DIR.")
    message(STATUS "Si estás en Windows y quieres usar la copia incluida en 'lib/', ejecuta con -DUSE_BUNDLED_SFML=ON y asegúrate de que 'lib/' contiene el paquete CMake adecuado.")
    message(FATAL_ERROR "SFML no encontrada. Provee SFML o ajusta USE_BUNDLED_SFML/SFML_DIR.")
endif()

# Build SFML libs variable
if(TARGET SFML::Graphics)
    set(SFML_LIBS SFML::Graphics SFML::Window SFML::System SFML::Audio)
elseif(DEFINED SFML_LIBRARIES)
    set(SFML_LIBS ${SFML_LIBRARIES})
else()
    # Fallback to link by name
    set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio)
endif()

# Recoger fuentes (reconfigurar automáticamente si se añaden archivos)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")

# Ejecutable
add_executable(UchronyGame_Executable ${SOURCE_FILES})
target_include_directories(UchronyGame_Executable PRIVATE Include)
target_compile_features(UchronyGame_Executable PUBLIC cxx_std_17)

# Vincula SFML usando la variable calculada
target_link_libraries(UchronyGame_Executable PRIVATE ${SFML_LIBS})

# Rutas de salida por configuración (útil en Windows/Visual Studio)
set_target_properties(UchronyGame_Executable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
)

# Mensaje final
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "SFML Found: ${SFML_FOUND}")
message(STATUS "SFML_LIBS: ${SFML_LIBS}")
