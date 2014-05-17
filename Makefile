CC=g++
CFLAGS= -Iinclude/ -Llib/SFML/ -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,\$$ORIGIN/../lib/SFML/ -std=c++11

all:  game

invalidmagic: game.o
	$(CC) build/game.o $(CFLAGS) -o bin/game

game: src/game.cpp
	$(CC) src/game.cpp $(CFLAGS) -c -o build/game.o 


