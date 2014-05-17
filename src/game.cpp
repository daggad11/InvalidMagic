#include <SFML/Graphics.hpp>
#include "world.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Invalid Magic");
	sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	sf::Clock timer;
	World world(&window, &view);
	
	view.setCenter(world.getPlayer()->getX()*Tile::tileSize, world.getPlayer()->getY()*Tile::tileSize);
	window.setView(view);
	timer.restart();

  while (window.isOpen()) {
		//event handling
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
		//keyboard input for player
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
