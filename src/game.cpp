#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstdio>
#include "world.hpp"
#include "resources.hpp"
#include <sstream>

int Tile::tileSize;

int main(int argc, char* argv[]) {
	//default window sizing
	int width = 800;
	int height = 600;

	//////////////////////////////
	// Cmd Line Arg  Processing //
	//////////////////////////////
	if (argc == 3) {
		width = atoi(argv[1]);
		height = atoi(argv[2]);
	}
	else if (argc > 3 || argc == 2)
	{
		std::cout <<" Usage: <height> <width>." << std::endl;
		return 0;
	}

	/////////////////////
	// Window Creation //
	/////////////////////
	sf::RenderWindow window(sf::VideoMode(width, height), "Invalid Magic");
	Tile::tileSize = window.getSize().x/20;
	sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	
	/////////////////
	// FPS Monitor //
	/////////////////
	sf::Clock timer;
	sf::Font font;
	font.loadFromFile("resources/arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setCharacterSize(12);
	std::stringstream s;
	timer.restart();

	////////////////
	// Load World //
	////////////////
	Resources::init();
	World world(&window, &view, false, &timer);

	view.setCenter(world.getPlayer()->getX()*Tile::tileSize, world.getPlayer()->getY()*Tile::tileSize);

	window.setView(view);
	

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{	
			if (event.type == sf::Event::Closed) {
				window.close();	
			}
		}
		//keyboard input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		/////////////////////
		// Player Movement //
		/////////////////////
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

		//////////////////
		// Update World //
		//////////////////
		world.update();

		///////////////////
		// Determine FPS //
		///////////////////
		s.str("");
		s << "FPS:" << (int)(1.0/(timer.restart()).asSeconds());
	    text.setString(s.str());
	    text.setPosition(view.getCenter().x - window.getSize().x/2, view.getCenter().y - window.getSize().y/2);
	    
	    window.clear(sf::Color::Black);
		
	    ////////////////
	    // Draw World //
	    ////////////////
		world.draw();	

		//////////////////////
		// Draw FPS + Debug //
		//////////////////////
		window.draw(text);
	    window.display();
  	}
  return 0;
}
