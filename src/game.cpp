#include <SFML/Graphics.hpp>
#include <fstream>
#include "world.hpp"

int Tile::tileSize;

int main() {
	Tile::tileSize = 64;
  sf::RenderWindow window(sf::VideoMode(1600, 900), "Invalid Magic");
	sf::Clock timer;
	sf::View view(sf::FloatRect(0, 0, Tile::tileSize * 100, (Tile::tileSize * 100) * window.getSize().y/window.getSize().x));

	std::ifstream saveFile("data/world.save");
	World world(&window, &view, saveFile);
	saveFile.close();
	
	view.setCenter(world.getPlayer()->getX()*Tile::tileSize, world.getPlayer()->getY()*Tile::tileSize);
	window.setView(view);
	timer.restart();

  while (window.isOpen()) {
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
		
		world.update(timer.getElapsedTime().asSeconds());
		timer.restart();
    window.clear(sf::Color::Black);
		world.draw();
    window.display();
  }
  return 0;
}
