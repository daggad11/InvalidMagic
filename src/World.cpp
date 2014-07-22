#include "World.hpp"
#include <iostream>

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

World::World(sf::Clock* timer, sf::View* view) {
	this->timer = timer;
	this->view = view;

	//creating textures
	textures[EntityType::PLAYER] = sf::Texture();
	textures[EntityType::TREE] = sf::Texture();
	textures[EntityType::ZOMBIE] = sf::Texture();
	textures[EntityType::MERCHANT] = sf::Texture();

	//loading textures
	textures[EntityType::PLAYER].loadFromFile("resources/playerFemale.png");
	textures[EntityType::TREE].loadFromFile("resources/tree.png");
	textures[EntityType::ZOMBIE].loadFromFile("resources/zombie.png");
	textures[EntityType::MERCHANT].loadFromFile("resources/merchantMale.png");

	//creating 10x10 tileMap
	genMap(100, 100);

	//creating player
	player = Player(&npcs, timer, 64, sf::Vector2i(20, 40), sf::Vector2i(1, 1), &entityMap, &tileMap, &textures[EntityType::PLAYER]);

	//creating weapons
	createWeapons();

	//generating 10 zombies
	int zombiesLeft = 10;
	while (zombiesLeft > 0) {
		sf::Vector2i position(rand() % entityMap.size(), rand() % entityMap[0].size());
		if (mapClear(position, sf::Vector2i(1, 1))) {
			createNPC(position, EntityType::ZOMBIE);
			zombiesLeft--;
		}
	}

	//generating merchant
	createNPC(sf::Vector2i(22, 41), EntityType::MERCHANT);
}


void World::update() {
	player.update();

	//running all npcs update functions
	for (int a = 0; a < npcs.size(); a++) {
		if (!npcs[a].update()) {
			npcs.erase(npcs.begin()+a);
		}
	}
}

Player* World::getPlayer() {
	return &player;
}

/////////////////////
//PRIVATE FUNCTIONS//
/////////////////////

void World::genMap(int width, int height) {
	
	//seeding random num generator
	srand (time(NULL));

	//pushing back dirt into a vector to pass to tilemap and pushing back nulls into entitymap
	std::vector<std::vector<int>> tempTiles;
	for (int a = 0; a < width; a++) {
		entityMap.push_back(std::vector<Entity*>());
		tempTiles.push_back(std::vector<int>());
		
		for (int b = 0; b < height; b++) {
			//generating random dirt
			tempTiles[a].push_back(TileMap::TileType::GRASS);
			entityMap[a].push_back(NULL);
		}
	}

	//generating tilemap
	tileMap.load(tempTiles, "resources/tiles.png", 64);

	//creating road
	paint(sf::Vector2i(0, 48), sf::Vector2i(100, 1), TileMap::TileType::CONCRETE);
	paint(sf::Vector2i(0, 49), sf::Vector2i(100, 1), TileMap::TileType::ROADHOR);
	paint(sf::Vector2i(0, 50), sf::Vector2i(100, 1), TileMap::TileType::CONCRETE);

	//generating forests
	genForest(sf::Vector2i (30, 0), sf::Vector2i(70, 48), 7);
	genForest(sf::Vector2i (30, 51), sf::Vector2i(70, 49), 7);
}

void World::genForest(sf::Vector2i startPosition, sf::Vector2i size, int density) {
	paint(startPosition, size, TileMap::TileType::DIRT);
	for (int a = startPosition.x; a < startPosition.x + size.x; a++) {
		for (int b = startPosition.y; b < startPosition.y + size.y; b++) {
			//decitding whether to create a tree 1/(10-density) chance
			if (rand() % (10-density) == 0)
				createObject(sf::Vector2i(a, b), EntityType::TREE);
		}
	}
}

void World::paint(sf::Vector2i startPosition, sf::Vector2i size, int type) {
	std::vector<std::vector<int>> tiles = tileMap.getTiles();

	for (int a = startPosition.x; a < startPosition.x + size.x; a++) {
		for (int b = startPosition.y; b < startPosition.y + size.y; b++) {
			tiles[a][b] = type;
		}
	}
	tileMap.setTiles(tiles);
}

void World::createNPC(sf::Vector2i position, int type) {
	std::map<int, float> stats;

	//ZOMBIE NPC
	if (type == EntityType::ZOMBIE) {
		stats[Creature::StatName::SPEED] = 20;
		stats[Creature::StatName::HEALTH] = 100;
		stats[Creature::StatName::ATTACK] = 10;
		stats[Creature::StatName::DEFENSE] = 10;
		stats[Creature::StatName::BASEDAMAGE] = 10;
		stats[Creature::StatName::DETECTIONRANGE] = 5;
		stats[Creature::StatName::ATTACKTIME] = 1;

		npcs.push_back(NPC(NPC::lastId, NPC::Type::FOLLOW, NPC::Type::MELEE, &player, stats, timer, 64, position, sf::Vector2i(1, 1), &entityMap, &tileMap, &textures[EntityType::ZOMBIE]));
	}

	//MERCHANT NPC
	if (type == EntityType::MERCHANT) {
		stats[Creature::StatName::SPEED] = -1000;
		stats[Creature::StatName::HEALTH] = 500;
		stats[Creature::StatName::ATTACK] = 10;
		stats[Creature::StatName::DEFENSE] = 50;
		stats[Creature::StatName::BASEDAMAGE] = 10;

		npcs.push_back(NPC(NPC::lastId, NPC::Type::PASSIVE, NPC::Type::NONE, &player, stats, timer, 64, position, sf::Vector2i(1, 1), &entityMap, &tileMap, &textures[EntityType::MERCHANT]));	
		npcs[npcs.size()-1].setMerchant(true);	

		//giving merchant weapons
		for (auto weapon : weapons) {
			npcs[npcs.size()-1].addWeapon(weapon);
		}
	}
}

void World::createObject(sf::Vector2i position, int type) {
	if (type == EntityType::TREE) {
		objects.push_back(Entity(64, position, sf::Vector2i(1, 1), &entityMap, &tileMap, &textures[EntityType::TREE]));
	}
}

void World::createWeapons() {
	std::map<int, float> statModifiers;

	//sword
	statModifiers[Weapon::StatName::ATTACK] = 5;
	statModifiers[Weapon::StatName::DEFENSE] = 5;
	statModifiers[Weapon::StatName::BASEDAMAGE] = 5;
	weapons.push_back(Weapon("sword", Weapon::Type::MELEE, statModifiers, 0.5, 10, "resources/sword.png"));

	//scythe
	statModifiers[Weapon::StatName::ATTACK] = 10;
	statModifiers[Weapon::StatName::DEFENSE] = 0;
	statModifiers[Weapon::StatName::BASEDAMAGE] = 10;
	weapons.push_back(Weapon("scythe", Weapon::Type::MELEE, statModifiers, 1, 15, "resources/scythe.png"));
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(tileMap, states);

	//drawing all objects
	for (Entity object : objects) { 
		target.draw(object);
	}
	
	target.draw(player);
		
	//drawing all npcs
	for (int a = 0; a < npcs.size(); a++) {
		target.draw(npcs[a]);
	}

}

bool World::mapClear(sf::Vector2i position, sf::Vector2i size) {
	for (int a = position.x; a < position.x + size.x; a++) {
		for (int b = position.y; b < position.y + size.y; b++) {
			if (a < 0 || a > entityMap.size() - 1 || b < 0 || b > entityMap[0].size() - 1)
				return false;
			if (entityMap[a][b] != NULL)
				return false;
		}
	}
	return true;
}