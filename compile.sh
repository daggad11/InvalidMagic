g++ src/game.cpp -o bin/game -Iinclude/ -Llib/SFML/ -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,\$ORIGIN/../lib/SFML/ -std=c++11