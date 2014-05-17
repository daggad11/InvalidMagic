CC=g++
CFLAGS= -Iinclude/ -Llib/SFML/ -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,\$$ORIGIN/../lib/SFML/ -std=c++11

all:  game

game: src/game.cpp
	$(CC) src/game.cpp $(CFLAGS) -o bin/game
