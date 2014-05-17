CC=g++
CFLAGS= -Iinclude/ -Llib/SFML/ -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,\$$ORIGIN/../lib/SFML/ -std=c++11

all: invalidmagic

invalidmagic: game.o entity.o
	$(CC) build/game.o build/entity.o $(CFLAGS) -o bin/game

game.o: src/game.cpp
	$(CC) src/game.cpp $(CFLAGS) -c -o build/game.o

entity.o: src/entity.cpp
	$(CC) src/entity.cpp $(CFLAGS) -c -o build/entity.o


