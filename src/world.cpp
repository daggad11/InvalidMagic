#include "world.hpp"

World::World(sf::RenderWindow* window, sf::View* view) {
	this->window = window;
	
	generate();

	textures.push_back(new sf::Texture());
	textures[2]->loadFromFile("resources/player.png");
	player = Player(window, 1, 1, 1, 1, textures[2], 1, view);
}

World::~World(){
	//tonodo
}

void World::generate() {
	srand(time(NULL));

	textures.push_back(new sf::Texture());
	textures.push_back(new sf::Texture());
	textures[0]->loadFromFile("resources/dirt1.png");
	textures[1]->loadFromFile("resources/grass.png");

	for (int a = 0; a < 100; a++) {
		tiles.push_back(std::vector<Tile>());
		for (int b = 0; b < 100; b++) {
			tiles[a].push_back(Tile(window, a, b, Tile::tileSize, Tile::tileSize, textures[rand()%2]));
		}
	}
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
