#include "tile.hpp"

Tile::Tile() {
	//todo
}

Tile::~Tile() {
	//todo
}

Tile::Tile(sf::RenderWindow* window, int x, int y, int width, int height, std::string type)
{
	this->window = window;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->texture = Resources::getTexture(type);
	this->type = type;

	generateArray();
}

void Tile::generateArray()
{
  	vertices = sf::VertexArray(sf::Quads, 4);
	vertices[0] = sf::Vertex(sf::Vector2f(x*width, y*height), sf::Vector2f(0, 0));
	vertices[1] = sf::Vertex(sf::Vector2f((x+1)*width, y*height), sf::Vector2f(texture->getSize().x, 0));
	vertices[2] = sf::Vertex(sf::Vector2f((x+1)*width, (y+1)*height), sf::Vector2f(texture->getSize().x, texture->getSize().y));
	vertices[3] = sf::Vertex(sf::Vector2f(x*width, (y+1)*height), sf::Vector2f(0, texture->getSize().y));
}

void Tile::draw()
{
	window->draw(vertices, texture);
}

void Tile::setTexture(sf::Texture* texture)
{
	this->texture = texture;
}

std::string Tile::getType() {
	return type;
}

int Tile::getX() {
	return x;
}

int Tile::getY() {
	return y;
}
