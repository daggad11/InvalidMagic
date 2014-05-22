CC := g++
CXX := $(CC)
CFLAGS := -Iinclude/ -g -std=c++11
LDFLAGS := -Llib/SFML/ -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,\$$ORIGIN/../lib/SFML/
OBJECTS := build/game.o build/entity.o build/creature.o build/player.o build/world.o build/tile.o build/object.o build/npc.o build/resources.o build/item.o build/debug.o
OBJS := $(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))

all: bin/game

#bin/game: $(OBJECTS)
#	$(CC) $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o bin/game

build/game.o: src/game.cpp
	$(CC) src/game.cpp $(CFLAGS) $(LDFLAGS) -c -o build/game.o

#build/resources.o: src/resources.cpp include/resources.hpp
#	$(CC) src/resources.cpp $(CFLAGS) $(LDFLAGS) -c -o build/resources.o

#build/tile.o: src/tile.cpp include/tile.hpp
#	$(CC) src/tile.cpp $(CFLAGS) $(LDFLAGS) -c -o build/tile.o

#build/item.o: src/item.cpp include/item.hpp
#	$(CC) src/item.cpp $(CFLAGS) $(LDFLAGS) -c -o build/item.o

#build/entity.o: src/entity.cpp include/entity.hpp build/tile.o build/resources.o
#	$(CC) src/entity.cpp $(CFLAGS) $(LDFLAGS) -c -o build/entity.o

#build/object.o: src/object.cpp include/object.hpp build/entity.o
#	$(CC) src/object.cpp $(CFLAGS) $(LDFLAGS) -c -o build/object.o

#build/creature.o: src/creature.cpp include/creature.hpp build/entity.o
#	$(CC) src/creature.cpp $(CFLAGS) $(LDFLAGS) -c -o build/creature.o

#build/player.o: src/player.cpp include/player.hpp build/creature.o
#	$(CC) src/player.cpp $(CFLAGS) $(LDFLAGS) -c -o build/player.o

#build/npc.o: src/npc.cpp include/npc.hpp build/creature.o
#	$(CC) src/npc.cpp $(CFLAGS) $(LDFLAGS) -c -o build/npc.o

#build/world.o: src/world.cpp include/world.hpp build/player.o build/tile.o
#	$(CC) src/world.cpp $(CFLAGS) $(LDFLAGS) -c -o build/world.o

#build/debug.o: src/debug.cpp include/debug.hpp
#	$(CC) src/debug.cpp $(CFLAGS) -c -o build/debug.o

build/%.o: src/%.cpp include/%.hpp
	$(CC) $< $(CFLAGS) $(LDFLAGS) -c -o $@

bin/game: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o bin/game 

clean: 
	rm build/*
	rm bin/game
