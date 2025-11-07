# Compilador de C++
CXX = g++

# --- Detección de SFML (Tu sección original, ¡está perfecta!) ---
# Intenta obtener las banderas de SFML via pkg-config
PKG_CONFIG := $(shell command -v pkg-config 2>/dev/null || true)
SFML_CFLAGS := $(if $(PKG_CONFIG),$(shell pkg-config --cflags sfml-all 2>/dev/null),)
SFML_LIBS := $(if $(PKG_CONFIG),$(shell pkg-config --libs sfml-all 2>/dev/null),)

# Fallback para Homebrew si pkg-config no está disponible
ifeq ($(SFML_CFLAGS),)
	HOMEBREW_PREFIX := $(shell brew --prefix 2>/dev/null || echo /opt/homebrew)
	SFML_CFLAGS := -I$(HOMEBREW_PREFIX)/include
	SFML_LIBS := -L$(HOMEBREW_PREFIX)/lib
endif
# --- Fin de la sección de SFML ---

# Banderas de compilación
# -IInclude (con 'I' mayúscula) para coincidir con tu carpeta
CXXFLAGS = -std=c++17 -Wall -IInclude -MMD -MP $(SFML_CFLAGS)

# Banderas del enlazador (Linker)
LDFLAGS = $(SFML_LIBS) -lsfml-graphics -lsfml-window -lsfml-system

# Directorios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Nombre del ejecutable
TARGET = $(BIN_DIR)/demo

# 1. Encuentra TODOS los archivos .cpp recursivamente
SOURCES = $(shell find $(SRC_DIR) -name "*.cpp")

# 2. Crea una lista de archivos objeto (.o) que imita la estructura de carpetas
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# 3. Crea una lista de archivos de dependencia (para auto-actualización)
DEPS = $(OBJECTS:.o=.d)

# Regla principal: se ejecuta por defecto con 'make'
all: $(TARGET)

# Regla para enlazar los archivos objeto y crear el ejecutable final
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Asegura que el directorio bin exista
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# 4. Regla patrón MEJORADA para compilar .cpp a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Archivos generados eliminados."

# Regla para reconstruir desde cero
rebuild: clean all

# Ejecutar el binario
run: $(TARGET)
	@./$(TARGET)

# Phony targets no representan archivos
.PHONY: all clean rebuild run

# Incluir archivos de dependencias generados automáticamente (si existen)
-include $(DEPS)