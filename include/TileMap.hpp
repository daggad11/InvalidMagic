#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <vector>
#include "SFML/Graphics.hpp"

/*A TileMap stores an vector of integers that represent tiles.
It can be drawn and return the status effects of a tile at a certain position.
A tile is not encapsulated anywhere but it is essentially a terrain that has a texture and possible status effects.
Tiles are handled completely by tilemaps, they are not actually objects*/

class TileMap : public sf::Drawable, public sf::Transformable {
public:
	enum TileType { DIRT1, DIRT2, DIRT3, GRASS, BLANK1, BlANK2, WATER, BLANK3, BLANK4 };

	TileMap(); //default constructor
	void load(std::vector<std::vector<int>> tiles, std::string tileSet, int tileSize); //loads tiles and creates vertex array

private:
	int tileSize; //size of tiles in pixels

	std::vector<std::vector<int>> tiles; //vector storing all the tiles as integers representing tile types
	sf::VertexArray vertices; //contains texture vertices to be drawn
	sf::Texture tileSet; //texture with all tiles to be drawn

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //virtual function from drawable that allows map to be drawn by window
};

#endif