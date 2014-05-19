#include "resources.hpp"

std::map<std::string, sf::Texture> Resources::textures;

void Resources::init() {
	textures["player"] =  sf::Texture();
	textures["dirt1"] = sf::Texture();
	textures["dirt2"] = sf::Texture();
	textures["grass"] = sf::Texture();
	textures["rock"] = sf::Texture();

	textures["player"].loadFromFile("resources/player.png");
	textures["dirt1"].loadFromFile("resources/dirt1.png");
	textures["dirt2"].loadFromFile("resources/dirt2.png");
	textures["grass"].loadFromFile("resources/grass.png");
	textures["rock"].loadFromFile("resources/rock.png");
}

Resources::~Resources() {

}

Resources::Resources() {

}

sf::Texture* Resources::getTexture(std::string texture) {
	return &textures[texture];
}
