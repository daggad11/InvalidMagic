CC := g++
CXX := $(CC)
CFLAGS := -I include/ -I ~/SFML/include -g -std=c++11
LDFLAGS := -L ~/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
OBJS := $(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))

all: bin/game

sandwich: all

bin/game: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o bin/game

build/Game.o: src/Game.cpp
	$(CC) src/Game.cpp $(CFLAGS) $(LDFLAGS) -c -o build/Game.o

build/%.o: src/%.cpp include/%.hpp
	$(CC) $< $(CFLAGS) $(LDFLAGS) -c -o $@

clean:
	rm build/*
	rm bin/game

.PHONY: clean
