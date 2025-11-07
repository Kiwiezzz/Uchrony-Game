INCL_FILES = $(wildcard Include/**/*.hpp)
SRC_FILES = $(wildcard src/*.cpp)

LSFM_STUFF = -lsfml-graphics -lsfml-window -lsfml-system
MY_FLAGS = -std=c++17


demo: $(INCL_FILES) $(SRC_FILES)
	g++ src/demo.cpp $(MY_FLAGS) -o demo -I Include $(LSFM_STUFF)