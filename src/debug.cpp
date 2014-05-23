#include "debug.hpp"

sf::Clock Debug::timer;
sf::Text Debug::text;
sf::RenderWindow* Debug::window;
sf::View* Debug::view;
std::stringstream Debug::stream;
std::vector<std::pair<std::string, int*> > Debug::pairs;

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
	timer.restart();
}

void Debug::setString(std::string s, int* value)
{
	pairs.push_back(std::pair<std::string, int*>(s, value));
}	

void Debug::draw()
{
	if (timer.getElapsedTime().asMilliseconds() > 250)
	{
		stream.str(""); //reset stringstream
		for (auto pair: pairs)
		{
			stream << pair.first << ": " << *(pair.second) << std::endl;
		}
		text.setString(stream.str());
		text.setPosition(view->getCenter().x - window->getSize().x/2, view->getCenter().y - window->getSize().y/2);
		window->draw(text);
		timer.restart();
	}
	else
	{
		text.setPosition(view->getCenter().x - window->getSize().x/2, view->getCenter().y - window->getSize().y/2);
		window->draw(text);
	}
}