INCL_FILES = $(wildcard Include/*.hpp)
INCL_FILES2 = $(wildcard Include/**/*.hpp)

SRC_FILES = $(wildcard src/*.cpp) ## Aquí incluye demo .cpp
SRC_FILES2 = $(wildcard src/**/*.cpp)

LSFM_STUFF = -lsfml-graphics -lsfml-window -lsfml-system
MY_FLAGS = -std=c++17

demo: $(INCL_FILES) $(INCL_FILES2) $(SRC_FILES) $(SRC_FILES2)
	g++ src/demo.cpp $(MY_FLAGS) -o demo -I Include $(LSFM_STUFF)