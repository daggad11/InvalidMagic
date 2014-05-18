#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>
#include "resources.hpp"

class Tile {
public:
	Tile();
	Tile(sf::RenderWindow* window, int x, int y, int width, int height, std::string type);
	~Tile();
	void setTexture(sf::Texture* t);
	void draw();
	std::string getType();
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
	std::string type;
};

#endif
