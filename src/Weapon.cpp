#include "Weapon.hpp"

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

Weapon::Weapon() {
	//do nothing
}

Weapon::Weapon(std::string name, bool type, std::map<int, float> statModifiers, float hitTime, int price, std::string texture) {
	this->name = name;
	this->type = type;
	this->statModifiers = statModifiers;
	this->hitTime = hitTime;
	this->price = price;
	this->texture.loadFromFile(texture);

	//making vertices into quad
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(4);

	//setting up texture for vertices
	vertices[0].texCoords = sf::Vector2f(0, 0);
	vertices[1].texCoords = sf::Vector2f(64, 0);
	vertices[2].texCoords = sf::Vector2f(64, 64);
	vertices[3].texCoords = sf::Vector2f(0, 64);
}

std::map<int, float> Weapon::getStatModifiers() {
	return statModifiers;
}

float Weapon::getHitTime() {
	return hitTime;
}

bool Weapon::getType() {
	return type;
}

std::string Weapon::getName() {
	return name;
}

int Weapon::getPrice() {
	return price;
}

void Weapon::setPosition(float x, float y, float width, float height) {
	vertices[0].position = sf::Vector2f(x, y);
	vertices[1].position = sf::Vector2f(x + width, y);
	vertices[2].position = sf::Vector2f(x + width, y + height);
	vertices[3].position = sf::Vector2f(x, y + height);
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.texture = &texture;
	target.draw(vertices, states);
}