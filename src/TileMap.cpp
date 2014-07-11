#include "TileMap.hpp"

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

TileMap::TileMap() {
	//does nothing
} 

void TileMap::load(std::vector<std::vector<int>> tiles, std::string tileSet, int tileSize) {
	this->tileSize = tileSize;
	this->tiles = tiles;
	this->tileSet.loadFromFile(tileSet);

	//storing width and height of texture
	int texWidth = this->tileSet.getSize().x;
	int texHeight = this->tileSet.getSize().y;

	//getting width and height from vector
	int width = tiles.size();
	int height = tiles[0].size();

	//setting up vertex array to store tiles
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(width * height * 4);


	for (int a = 0; a < width; a++) {
		for (int b = 0; b < height; b++) {
			//getting value at position in array
			int tileNumber = tiles[a][b];

			//finding position in tileset
			int texPosX = tileNumber % (texWidth / tileSize);
			int texPosY = tileNumber / (texWidth / tileSize); 

			//getting pointer to current quad
			sf::Vertex* quad = &(this->vertices[(a + b * width) * 4]);

			//positioning vertices
			quad[0].position = sf::Vector2f(a * tileSize, b * tileSize);
			quad[1].position = sf::Vector2f((a+1) * tileSize, b * tileSize);
			quad[2].position = sf::Vector2f((a+1) * tileSize, (b+1) * tileSize);
			quad[3].position = sf::Vector2f(a * tileSize, (b+1) * tileSize);

			//positioning tex coords for vertices
			quad[0].texCoords = sf::Vector2f(texPosX * tileSize, texPosY * tileSize);
			quad[1].texCoords = sf::Vector2f((texPosX+1) * tileSize, texPosY * tileSize);
			quad[2].texCoords = sf::Vector2f((texPosX+1) * tileSize, (texPosY+1) * tileSize);
			quad[3].texCoords = sf::Vector2f(texPosX * tileSize, (texPosY+1) * tileSize);
		}
	}

}

/////////////////////
//PRIVATE FUNCTIONS//
/////////////////////

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//apply the transform
	states.transform *= getTransform();

	//apply tileset texture
	states.texture = &tileSet;

	//draw vertex array
	target.draw(vertices, states);

}