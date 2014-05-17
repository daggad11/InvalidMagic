#include "world.hpp"

int Tile::tileSize;

World::World(sf::RenderWindow* window, sf::View* view) {
	this->window = window;
	Tile::tileSize = 32;

	//tilemap
	textures.push_back(new sf::Texture());
	textures[0]->loadFromFile("resources/dirt1.png");
	for (int a = 0; a < 100; a++) {
		tiles.push_back(std::vector<Tile>());
		for (int b = 0; b < 100; b++) {
			tiles[a].push_back(Tile(window, a, b, Tile::tileSize, Tile::tileSize, textures[0]));
		}
	}

	//player
	textures.push_back(new sf::Texture());
	textures[1]->loadFromFile("resources/grass.png");
	player = Player(window, 1, 1, 1, 1, textures[1], 1, view);
}

World::~World(){
	//tonodo
}

void World::draw()
{
	for (auto row: tiles)
		for (auto tile : row)
			tile.draw();

	player.draw();
}

void World::update(double time) {
	player.update(time);
}

Player* World::getPlayer()
{
	return &player;
}
