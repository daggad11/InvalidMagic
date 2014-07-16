#include "UserInterface.hpp"
#include <iostream>

UserInterface::UserInterface(Player* player, sf::View* view, sf::RenderWindow* window) {
	this->player = player;
	this->view = view;
	this->window = window;

	//setting position && size of healthbars
	healthBar[0].setSize(sf::Vector2f(130, 20));
	healthBar[1].setSize(sf::Vector2f(128, 16));

	healthBar[0].setPosition(view->getCenter().x + view->getSize().x/4 - 130, view->getCenter().y - view->getSize().y);
	healthBar[1].setPosition(view->getCenter().x + view->getSize().x/4 - 130, view->getCenter().y - view->getSize().y + 2);

	//setting color of healthbars
	healthBar[0].setFillColor(sf::Color::Black);
	healthBar[1].setFillColor(sf::Color::Red);
	healthBar[1].setOutlineColor(sf::Color(102, 0, 0));
	healthBar[1].setOutlineThickness(2);
}

void UserInterface::update() {
	//setting healthbar to correct size
	healthBar[1].setSize(sf::Vector2f(128 * (player->getStats()[Player::StatName::HEALTH] / player->getBaseStats()[Player::StatName::HEALTH]), 16));

	//repositioning healthbar
	healthBar[0].setPosition(view->getCenter().x + view->getSize().x/2 - 130, view->getCenter().y - view->getSize().y/2);
	healthBar[1].setPosition(view->getCenter().x + view->getSize().x/2 - 130, view->getCenter().y - view->getSize().y/2 + 2);
}

void UserInterface::weaponsMenu() {
	bool running = true;

	//clock used for timing
	sf::Clock clock;

	//setting up text for menu
	sf::Font font;
	std::vector<sf::Text> weaponsText;
	sf::Text messageText;

	//highlight bar
	sf::RectangleShape highlightBar;
	highlightBar.setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y - view->getSize().y / 2);
	highlightBar.setSize(sf::Vector2f(view->getSize().x, 25));
	highlightBar.setFillColor(sf::Color(255, 255, 255, 25));

	float lastMove = clock.getElapsedTime().asSeconds();

	font.loadFromFile("resources/stocky.ttf");

	//loading weapons into menu
	for (int a = 0; a < player->getWeapons().size(); a++) {
		weaponsText.push_back(sf::Text());
		weaponsText[a].setCharacterSize(20);
		weaponsText[a].setFont(font);
		weaponsText[a].setString(player->getWeapons()[a].getName());
		weaponsText[a].setPosition(view->getCenter().x - 40, view->getCenter().y - view->getSize().y / 2 + a*20);
	}

	//setting up message Text
	messageText.setCharacterSize(20);
	messageText.setFont(font);
	messageText.setString("Controls: (E)quip, (Esc)ape");
	messageText.setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y + view->getSize().y / 2 - 25);

	int selection = 0; //which weapon is currently selected

	while (running) {

		sf::Event event;
    while (window->pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
      	running = false;

      //controlling highlightbar
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && clock.getElapsedTime().asSeconds() > lastMove + 0.25) {
      	for (int a = 0; a < weaponsText.size(); a++) {
      			weaponsText[a].setPosition(weaponsText[a].getPosition().x, weaponsText[a].getPosition().y + 20);
      	}
      	selection--;
      	lastMove = clock.getElapsedTime().asSeconds();
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && clock.getElapsedTime().asSeconds() > lastMove + 0.25) {
      	for (int a = 0; a < weaponsText.size(); a++) {
      		weaponsText[a].setPosition(weaponsText[a].getPosition().x, weaponsText[a].getPosition().y - 20);
      	}
      	selection++;
      	lastMove = clock.getElapsedTime().asSeconds();
      }

      //equiping weapon
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
      	player->equipWeapon(player->getWeapons()[selection]);
      	running = false;
      }
    }

		window->clear();

		//drawing weapon names
		for (auto weapon : weaponsText) 
			window->draw(weapon);
		window->draw(highlightBar);
		window->draw(messageText);
    window->display();
	}
}

void UserInterface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(healthBar[0]);
	target.draw(healthBar[1]);
}
