#include "world.hpp"

World::World(sf::RenderWindow* window, sf::View* view, bool hasSave) {
	this->window = window;

	textures.push_back(new sf::Texture());
	textures.push_back(new sf::Texture());
	textures.push_back(new sf::Texture());
	textures.push_back(new sf::Texture());
	textures.push_back(new sf::Texture());
	textures[0]->loadFromFile("resources/dirt1.png");
	textures[1]->loadFromFile("resources/dirt2.png");
	textures[2]->loadFromFile("resources/grass.png");
	textures[3]->loadFromFile("resources/player.png");
	textures[4]->loadFromFile("resources/rock.png");
	
	if (hasSave)
		load();
	else
		generate();
	
	player = Player(window, 1, 1, 1, 1, textures[3], 1, view);
	tilemap[1][1] = &player;
}

World::~World(){
}

void World::generate() {
	srand(time(NULL));



	//drawing grass
	for (int a = 0; a < 100; a++) {
		tiles.push_back(std::vector<Tile>());
		for (int b = 0; b < 100; b++) {
			tiles[a].push_back(Tile(window, a, b, Tile::tileSize, Tile::tileSize, textures[2], 2));
		}
	}
	
	int ypos = rand() % 10;
	int type;
	for (int a = 0; a < 99; a++) {
		for (int b = 0; b < rand() % 3 + 4; b++) {
			
			if (rand() % 10 == 8)//specifically 8
				type = 1;
			else
				type = 0;

			tiles[a][ypos] = Tile(window, a, ypos, Tile::tileSize, Tile::tileSize, textures[type], type);
			
			if (rand() % 10 == 8)//specifically 8
				type = 1;
			else
				type = 0;

			tiles[a+1][ypos] = Tile(window, a+1, ypos, Tile::tileSize, Tile::tileSize, textures[type], type);
			if (rand() % 2 && ypos < 99)
				ypos++;
			else if (ypos > 0)
				ypos--;
		} 
	}

	objects.push_back(Object(window, 1, 1, 4, 4, textures[4], "rock"));
	tilemap[4][4] = &objects[0];
	
	std::cout << "World Generated" << std::endl;
}

void World::draw()
{
	for (auto row: tiles)
		for (auto tile : row)
			tile.draw();

	for (auto object : objects)
		object.draw();

	player.draw();
}

void World::update(double time) {
	player.update(time, tilemap);
}

Player* World::getPlayer()
{
	return &player;
}

void World::save() {
	std::ofstream file("data/world.save");
	file << tiles.size() << " " << tiles[0].size() << std::endl;

	//save tiles
	for (auto row : tiles) {
		for (auto tile : row) {
			file << tile.getType() << " " ;
		}
		file << std::endl;
	}

	//save objects
	file << objects.size() << std::endl;
	for (auto object : objects) {
		file << object.getWidth() << " " << object.getHeight() << " " << object.getX() << " " << object.getY() << " " << object.getMass() << " "  << object.getType() << std::endl;
	}
	file.close();
}

void World::load() {
	std::ifstream file("data/world.save");
	int tilesX, tilesY;
	file >> tilesX;
	file >> tilesY;

	//loading tiles
	int value;
	for (int a = 0; a < tilesX; a++) {
		tiles.push_back(std::vector<Tile>());
		for (int b = 0; b < tilesY; b++) {
			file >> value;
			tiles[a].push_back(Tile(window, a, b, Tile::tileSize, Tile::tileSize, textures[value], value));
		}
	}
	std::cout << "blah" << std::endl;
	//loading objects
	int numberOfObjects;
	file >> numberOfObjects;
	for (int a = 0; a < numberOfObjects; a++) {
		int width, height, x, y;
		std::string type;
		file >> width;
		file >> height;
		file >> x;
		file >> y;
		file >> type;
		objects.push_back(Object(window, width, height, x, y, textures[4], type));
		tilemap[x][y] = &objects[a];
	}

	file.close();
	std::cout << "World Loaded" << std::endl;
}
