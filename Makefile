# Compilador de C++
CXX = g++

# Try to get SFML flags via pkg-config (if available)
PKG_CONFIG := $(shell command -v pkg-config 2>/dev/null || true)
SFML_CFLAGS := $(if $(PKG_CONFIG),$(shell pkg-config --cflags sfml-all 2>/dev/null),)
SFML_LIBS := $(if $(PKG_CONFIG),$(shell pkg-config --libs sfml-all 2>/dev/null),)

# Fallback to Homebrew paths if pkg-config not available
ifeq ($(SFML_CFLAGS),)
    HOMEBREW_PREFIX := $(shell brew --prefix 2>/dev/null || echo /opt/homebrew)
    SFML_CFLAGS := -I$(HOMEBREW_PREFIX)/include
    SFML_LIBS := -L$(HOMEBREW_PREFIX)/lib
endif

# Banderas de compilación
# -std=c++17: Usa el estándar de C++17
# -Wall: Activa todas las advertencias
# -Iinclude: Le dice al compilador que busque archivos de cabecera en la carpeta 'include'
# -MMD -MP: Genera archivos de dependencia
CXXFLAGS = -std=c++17 -Wall -Iinclude -MMD -MP $(SFML_CFLAGS)

# Banderas del enlazador (Linker)
# -lsfml-graphics, -lsfml-window, -lsfml-system: Enlaza las bibliotecas de SFML necesarias
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system $(SFML_LIBS)

# Directorios
SRC_DIRS = src main
OBJ_DIR = obj
BIN_DIR = bin

vpath %.cpp $(SRC_DIRS)

# Nombre del ejecutable
TARGET = $(BIN_DIR)/uchrony.exe

# Encuentra todos los archivos .cpp en los directorios de fuentes
SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

# Genera los nombres de los archivos objeto (.o) en el directorio obj
OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SOURCES)))

# Regla principal: se ejecuta por defecto con 'make'
all: $(TARGET)

# Regla para enlazar los archivos objeto y crear el ejecutable final
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Ejecutable '$@' creado exitosamente."

# Asegura que el directorio bin exista antes de enlazar (order-only prerequisite)
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Regla patrón para compilar archivos .cpp a .o
# $< es el primer prerrequisito (el .cpp)
# $@ es el nombre del objetivo (el .o)
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR) && $(CXX) $(CXXFLAGS) -c $< -o $@

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
-include $(OBJECTS:.o=.d)
