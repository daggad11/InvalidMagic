#include "debug.hpp"

float Debug::average;
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
	//for (int i = 0; i < w->getSize().y/12; i++)
	//{
	//		pairs.push_back(std::pair<std::string, int*>("\n", nullptr));
	//} 
}

void Debug::setString(std::string s, int* value)
{
	pairs.push_back(std::pair<std::string, int*>(s, value));
}	

void Debug::draw()
{

	if (timer.getElapsedTime().asMilliseconds() > 200)
	{
		stream.str(""); //reset stringstream
		for (int i = 0; i < pairs.size(); i++)
		{
			if (pairs[i].second != nullptr)
			{
				if (i == 0)
				{
					int len = log10(average) + 1;
					stream << pairs[0].first << ": ";
					for (int j = 0; j < (4-len); j++)
						stream << " ";
				 	stream << floor(average) << std::endl;
				}
				else
				{
					stream << pairs[i].first << ": " << *(pairs[i].second) << std::endl;
				}
			}
			else
			{
				stream << pairs[i].first;
			}
		}
		text.setString(stream.str());
		text.setPosition(view->getCenter().x - window->getSize().x/2, view->getCenter().y - window->getSize().y/2);
		window->draw(text);
		timer.restart();
	}
	else
	{
		average = (average + *(pairs[0].second))/2.0;
		text.setPosition(view->getCenter().x - window->getSize().x/2, view->getCenter().y - window->getSize().y/2);
		window->draw(text);
	}
}