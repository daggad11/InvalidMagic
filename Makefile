CC=g++
CFLAGS= -Iinclude/ -Llib/SFML/ -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,\$$ORIGIN/../lib/SFML/ -g -std=c++11
OBJECTS= build/game.o build/entity.o build/creature.o build/player.o build/world.o build/tile.o build/object.o build/npc.o build/resources.o build/item.o

all: bin/game

bin/game: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o bin/game

build/game.o: src/game.cpp build/world.o build/resources.o 
	$(CC) src/game.cpp $(CFLAGS) -c -o build/game.o

build/resources.o: src/resources.cpp include/resources.hpp
	$(CC) src/resources.cpp $(CFLAGS) -c -o build/resources.o

build/tile.o: src/tile.cpp include/tile.hpp
	$(CC) src/tile.cpp $(CFLAGS) -c -o build/tile.o

build/item.o: src/item.cpp include/item.hpp
	$(CC) src/item.cpp $(CFLAGS) -c -o build/item.o

build/entity.o: src/entity.cpp include/entity.hpp build/tile.o build/resources.o
	$(CC) src/entity.cpp $(CFLAGS) -c -o build/entity.o

build/object.o: src/object.cpp include/object.hpp build/entity.o
	$(CC) src/object.cpp $(CFLAGS) -c -o build/object.o

build/creature.o: src/creature.cpp include/creature.hpp build/entity.o
	$(CC) src/creature.cpp $(CFLAGS) -c -o build/creature.o

build/player.o: src/player.cpp include/player.hpp build/creature.o
	$(CC) src/player.cpp $(CFLAGS) -c -o build/player.o

build/npc.o: src/npc.cpp include/npc.hpp build/creature.o
	$(CC) src/npc.cpp $(CFLAGS) -c -o build/npc.o

build/world.o: src/world.cpp include/world.hpp build/player.o build/tile.o
	$(CC) src/world.cpp $(CFLAGS) -c -o build/world.o


