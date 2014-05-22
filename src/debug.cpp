#include "debug.hpp"

sf::Text Debug::text;
std::vector<std::string> Debug::strings;
sf::RenderWindow* Debug::window;
sf::View* Debug::view;
std::stringstream Debug::stream;
std::map<std::string, int*> Debug::values;

Debug::Debug(){};
Debug::~Debug(){};

void Debug::init(sf::RenderWindow* w, sf::View* v)
{
	view = v;
	window = w;
	text = sf::Text();
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile("resources/arial.ttf"))
		font->loadFromFile("../resources/arial.ttf");
	text.setFont(*font);
	text.setColor(sf::Color::White);
	text.setCharacterSize(12);
	stream.str("");
}

void Debug::setString(std::string s, int* value)
{
	values[s] = value;
	strings.push_back(s);
}	

void Debug::draw()
{
	stream.str(""); //reset stringstream
	for (std::string s: strings)
	{
		stream << s << ": " << *(values[s]) << std::endl;
	}
	text.setString(stream.str());
	text.setPosition(view->getCenter().x - window->getSize().x/2, view->getCenter().y - window->getSize().y/2);
	window->draw(text);
}