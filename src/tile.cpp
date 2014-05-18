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
	this->t = Resources::getTexture(type);
	this->type = type;

	generateArray();
}

void Tile::generateArray()
{
  v = sf::VertexArray(sf::Quads, 4);
	v[0] = sf::Vertex(sf::Vector2f(x*width, y*height), sf::Vector2f(0, 0));
	v[1] = sf::Vertex(sf::Vector2f((x+1)*width, y*height), sf::Vector2f(t->getSize().x, 0));
	v[2] = sf::Vertex(sf::Vector2f((x+1)*width, (y+1)*height), sf::Vector2f(t->getSize().x, t->getSize().y));
	v[3] = sf::Vertex(sf::Vector2f(x*width, (y+1)*height), sf::Vector2f(0, t->getSize().y));
}

void Tile::draw()
{
	window->draw(v, t);
}

void Tile::setTexture(sf::Texture* t)
{
	this->t = t;
}

std::string Tile::getType() {
	return type;
}
