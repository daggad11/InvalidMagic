#include "World.hpp"
#include <iostream>

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

World::World(sf::Clock* timer) {
	this->timer = timer;

	//creating textures
	textures[EntityType::PLAYER] = sf::Texture();
	textures[EntityType::TREE] = sf::Texture();
	textures[EntityType::ZOMBIE] = sf::Texture();

	//loading textures
	textures[EntityType::PLAYER].loadFromFile("resources/playerFemale.png");
	textures[EntityType::TREE].loadFromFile("resources/tree.png");
	textures[EntityType::ZOMBIE].loadFromFile("resources/zombie.png");

	//creating 10x10 tileMap
	genMap(100, 100);

	//creating player
	player = Player(&npcs, timer, 64, sf::Vector2i(1, 1), sf::Vector2i(1, 1), &entityMap, &tileMap, &textures[EntityType::PLAYER]);

	//generating 10 zombies
	int zombiesLeft = 100;
	while (zombiesLeft > 0) {
		sf::Vector2i position(rand() % entityMap.size(), rand() % entityMap[0].size());
		if (mapClear(position, sf::Vector2i(1, 1))) {
			createNPC(position, EntityType::ZOMBIE);
			zombiesLeft--;
		}
	}

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
			tempTiles[a].push_back(rand() % 3);
			entityMap[a].push_back(NULL);
		}
	}

	//generating tilemap
	tileMap.load(tempTiles, "resources/tiles.jpg", 64);

	//generating forest
	for (int a = 10; a < 50; a += 2) {
		for (int b = 10; b < 50; b+= 2) {
			objects.push_back(Entity(64, sf::Vector2i(a, b), sf::Vector2i(1, 1), &entityMap, &tileMap, &textures[EntityType::TREE]));
		}
	}
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