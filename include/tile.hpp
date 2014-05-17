#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>

class Tile {
public:
	Tile();
	Tile(sf::RenderWindow* window, int x, int y, int width, int height, sf::Texture* t, int type);
	~Tile();
	void setTexture(sf::Texture* t);
	void draw();
	int getType();
	static int tileSize;
private:
	void generateArray();
	sf::VertexArray v;
	sf::Texture* t;
	sf::RenderWindow* window; 
	int width;
	int height;
	int x;
	int y;
	int type;
};

#endif
