CC=g++
CFLAGS= -Iinclude/ -Llib/SFML/ -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,\$$ORIGIN/../lib/SFML/ -std=c++11
OBJECTS= 

all: invalidmagic

invalidmagic: game.o entity.o creature.o player.o
	$(CC) $(OBJECTS) $(CFLAGS) -o bin/game

game.o: src/game.cpp
	$(CC) src/game.cpp $(CFLAGS) -c -o build/game.o

entity.o: src/entity.cpp
	$(CC) src/entity.cpp $(CFLAGS) -c -o build/entity.o

creature.o: src/creature.cpp entity.o
	$(CC) src/creature.cpp $(CFLAGS) -c -o build/creature.o

player.o: src/player.cpp creature.o entity.o
	$(CC) src/player.cpp $(CFLAGS) -c -o build/player.o


