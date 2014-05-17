#include <SFML/Graphics.hpp>
#include "world.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Invalid Magic");
	World world(&window);

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

    window.clear(sf::Color::Black);
		world.draw();
    window.display();
  }
  return 0;
}
