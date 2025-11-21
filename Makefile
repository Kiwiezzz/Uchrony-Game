INCL_FILES = $(wildcard Include/*.hpp)
INCL_FILES_SUB = $(wildcard Include/**/*.hpp)

SRC_FILES = $(wildcard src/*.cpp) ## Archivos .cpp de las carpeta principal
SRC_FILES_SUB = $(wildcard src/**/*.cpp) ## Archivos .cpp de las carpetas secundarias

LSFM_STUFF = -lsfml-graphics -lsfml-window -lsfml-system
MY_FLAGS = -std=c++17

demo: $(INCL_FILES) $(INCL_FILES_SUB) $(SRC_FILES) $(SRC_FILES_SUB)
	g++ $(SRC_FILES) $(SRC_FILES_SUB) $(MY_FLAGS) -o demo -I Include $(LSFM_STUFF) -g

## El -g es para que se pueda debugear