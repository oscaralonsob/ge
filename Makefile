# Makefile variables
CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs"
SRC_FOLDER = ./src/*.cpp\
			 ./src/Game/*.cpp\
			 ./src/Logger/*.cpp\
			 ./src/ECS/*.cpp\
			 ./src/Events/*.cpp\
			 ./src/AssetStore/*.cpp\
			 ./libs/imgui/*.cpp
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -llua5.3
OBJ_NAME = build/gameengine

compile:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FOLDER) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)