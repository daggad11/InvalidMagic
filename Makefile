CC=g++
CFLAGS= -Iinclude/ -Llib/SFML/ -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,\$$ORIGIN/../lib/SFML/ -std=c++11
OBJECTS= build/game.o build/entity.o build/creature.o build/player.o build/world.o build/tile.o

all: bin/game

bin/game: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o bin/game

build/game.o: src/game.cpp
	$(CC) src/game.cpp $(CFLAGS) -c -o build/game.o

build/entity.o: src/entity.cpp include/entity.hpp
	$(CC) src/entity.cpp $(CFLAGS) -c -o build/entity.o

build/creature.o: src/creature.cpp include/creature.hpp build/entity.o
	$(CC) src/creature.cpp $(CFLAGS) -c -o build/creature.o

build/player.o: src/player.cpp build/creature.o build/entity.o
	$(CC) src/player.cpp $(CFLAGS) -c -o build/player.o

build/tile.o: src/tile.cpp include/tile.hpp
	$(CC) src/tile.cpp $(CFLAGS) -c -o build/tile.o

build/world.o: src/world.cpp include/world.hpp build/player.o build/tile.o
	$(CC) src/world.cpp $(CFLAGS) -c -o build/world.o


