#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstdio>
#include "world.hpp"
#include "resources.hpp"
#include <sstream>

int Tile::tileSize;

int main(int argc, char* argv[]) {
	int width = 800;
	int height = 600;
	if (argc == 3) {
		width = atoi(argv[1]);
		height = atoi(argv[2]);
	}
  sf::RenderWindow window(sf::VideoMode(width, height), "Invalid Magic");
	Tile::tileSize = window.getSize().x/20;
	sf::Clock timer;
	sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	sf::Font font;
	font.loadFromFile("../resources/arial.ttf");
	sf::Text text;
	text.setFont(font);
	std::stringstream s;

	timer.restart();

	Resources::init();

	std::ifstream saveFile("data/world.save");
	World world(&window, &view, saveFile, &timer);
	saveFile.close();

	view.setCenter(world.getPlayer()->getX()*Tile::tileSize, world.getPlayer()->getY()*Tile::tileSize);

	window.setView(view);
	

  while (window.isOpen()) {
	sf::Event event;
	while (window.pollEvent(event))
	{	
		if (event.type == sf::Event::Closed) {
			world.save();
			window.close();	
		}
	}
	//keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		world.save();
		window.close();
	}
	//player movement
	bool up, down, left, right;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		up = true;
	else
		up = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		down = true;
	else
		down = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		right = true;
	else
		right = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		left = true;
	else
		left = false;
	world.getPlayer()->setMovementState(up, down, right, left);
	//end of keyboard input

	s.str("");
	world.update();
	s << "FPS:" << (1.0/(timer.restart()).asSeconds());
    text.setString(s.str());
    window.clear(sf::Color::Black);
	world.draw();	
	window.draw(text);
    window.display();
  }
  return 0;
}
