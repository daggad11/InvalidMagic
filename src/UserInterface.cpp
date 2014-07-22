#include "UserInterface.hpp"
#include <iostream>

UserInterface::UserInterface(Player* player, sf::View* view, sf::RenderWindow* window) {
	this->player = player;
	this->view = view;
	this->window = window;


	//setting position && size of healthbars
	healthBar[0].setSize(sf::Vector2f(128, 32));
	healthBar[1].setSize(sf::Vector2f(124, 28));

	healthBar[0].setPosition(view->getCenter().x + view->getSize().x/4 - 128, view->getCenter().y - view->getSize().y);
	healthBar[1].setPosition(view->getCenter().x + view->getSize().x/4 - 128, view->getCenter().y - view->getSize().y + 2);

	//setting color of healthbars
	healthBar[0].setFillColor(sf::Color::Black);
	healthBar[1].setFillColor(sf::Color::Red);
	healthBar[1].setOutlineColor(sf::Color(102, 0, 0));
	healthBar[1].setOutlineThickness(2);

	//setting up weapon box
	weaponBox.setSize(sf::Vector2f(60, 60));
	weaponBox.setPosition(healthBar[0].getPosition().x - 64, healthBar[0].getPosition().y + 2);
	weaponBox.setFillColor(sf::Color::White);
	weaponBox.setOutlineColor(sf::Color::Black);
	weaponBox.setOutlineThickness(2);
}

void UserInterface::update() {
	//setting healthbar to correct size
	healthBar[1].setSize(sf::Vector2f(128 * (player->getStats()[Player::StatName::HEALTH] / player->getBaseStats()[Player::StatName::HEALTH]) - 2, 28));

	//repositioning healthbar
	healthBar[0].setPosition(view->getCenter().x + view->getSize().x/2 - 128, view->getCenter().y - view->getSize().y/2);
	healthBar[1].setPosition(view->getCenter().x + view->getSize().x/2 - 128, view->getCenter().y - view->getSize().y/2 + 2);

	//repositioning weaponbox
	weaponBox.setPosition(healthBar[0].getPosition().x - 64, healthBar[0].getPosition().y + 2);

	//setting position of weapon
	player->getEquipedWeapon()->setPosition(weaponBox.getPosition().x, weaponBox.getPosition().y, 60, 60);
}

////////////////
//WEAPONS MENU//
////////////////

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
	highlightBar.setSize(sf::Vector2f(view->getSize().x, 15));
	highlightBar.setFillColor(sf::Color(255, 255, 255, 25));

	float lastMove = clock.getElapsedTime().asSeconds();

	font.loadFromFile("resources/stocky.ttf");

	//loading weapons into menu
	std::vector<Weapon> weapons = player->getWeapons();
	for (int a = 0; a < player->getWeapons().size(); a++) {
		std::map<int, float> statModifiers = weapons[a].getStatModifiers();

		weaponsText.push_back(sf::Text());
		weaponsText[a].setCharacterSize(12);
		weaponsText[a].setFont(font);
		weaponsText[a].setString(weapons[a].getName() + " -- Attack: " + std::to_string((int)statModifiers[Player::StatName::ATTACK]) + " -- Defense: " + std::to_string((int)statModifiers[Player::StatName::DEFENSE]) + " -- Base Damage: " + std::to_string((int)statModifiers[Player::StatName::BASEDAMAGE]) + " -- Attack Speed: " + std::to_string(weapons[a].getHitTime()));
		weaponsText[a].setPosition(view->getCenter().x - view->getSize().x/2, view->getCenter().y - view->getSize().y / 2 + a*12);
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
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && clock.getElapsedTime().asSeconds() > lastMove + 0.25 && selection != 0) {
      	for (int a = 0; a < weaponsText.size(); a++) {
      			weaponsText[a].setPosition(weaponsText[a].getPosition().x, weaponsText[a].getPosition().y + 12);
      	}
      	selection--;
      	lastMove = clock.getElapsedTime().asSeconds();
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && clock.getElapsedTime().asSeconds() > lastMove + 0.25 && selection != weaponsText.size()-1) {
      	for (int a = 0; a < weaponsText.size(); a++) {
      		weaponsText[a].setPosition(weaponsText[a].getPosition().x, weaponsText[a].getPosition().y - 12);
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

////////////////
//WEAPONS SHOP//
////////////////

void UserInterface::weaponsShop(NPC* npc) {
	bool running = true;

	//clock used for timing
	sf::Clock clock;

	//setting up text for menu
	sf::Font font;
	std::vector<sf::Text> weaponsText;
	sf::Text messageText;
	sf::Text goldText;

	//highlight bar
	sf::RectangleShape highlightBar;
	highlightBar.setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y - view->getSize().y / 2);
	highlightBar.setSize(sf::Vector2f(view->getSize().x, 15));
	highlightBar.setFillColor(sf::Color(255, 255, 255, 25));

	float lastMove = clock.getElapsedTime().asSeconds();

	font.loadFromFile("resources/stocky.ttf");

	//loading weapons into menu
	std::vector<Weapon> weapons = npc->getWeapons();
	for (int a = 0; a < npc->getWeapons().size(); a++) {
		std::map<int, float> statModifiers = weapons[a].getStatModifiers();

		weaponsText.push_back(sf::Text());
		weaponsText[a].setCharacterSize(12);
		weaponsText[a].setFont(font);
		weaponsText[a].setString(weapons[a].getName() + " -- Attack: " + std::to_string((int)statModifiers[Player::StatName::ATTACK]) + " -- Defense: " + std::to_string((int)statModifiers[Player::StatName::DEFENSE]) + " -- Base Damage: " + std::to_string((int)statModifiers[Player::StatName::BASEDAMAGE]) + " -- Attack Speed: " + std::to_string(weapons[a].getHitTime()) + " -- Price: " + std::to_string(weapons[a].getPrice()));
		weaponsText[a].setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y - view->getSize().y / 2 + a*12);
	} 

	//setting up message Text
	messageText.setCharacterSize(12);
	messageText.setFont(font);
	messageText.setString("Controls: Press E to purchase, press Esc to exit");
	messageText.setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y + view->getSize().y / 2 - 20);

	//setting up gold text
	goldText.setCharacterSize(12);
	goldText.setFont(font);
	goldText.setString("Gold: " + std::to_string(player->getGold()));
	goldText.setPosition(view->getCenter().x + view->getSize().x / 2 - 100, view->getCenter().y + view->getSize().y / 2 - 20);

	int selection = 0; //which weapon is currently selected

	while (running) {

		sf::Event event;
    while (window->pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
      	running = false;

      //controlling highlightbar
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && clock.getElapsedTime().asSeconds() > lastMove + 0.25 && selection != 0) {
      	for (int a = 0; a < weaponsText.size(); a++) {
      			weaponsText[a].setPosition(weaponsText[a].getPosition().x, weaponsText[a].getPosition().y + 12);
      	}
      	selection--;
      	lastMove = clock.getElapsedTime().asSeconds();
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && clock.getElapsedTime().asSeconds() > lastMove + 0.25 && selection != weaponsText.size()-1) {
      	for (int a = 0; a < weaponsText.size(); a++) {
      		weaponsText[a].setPosition(weaponsText[a].getPosition().x, weaponsText[a].getPosition().y - 12);
      	}
      	selection++;
      	lastMove = clock.getElapsedTime().asSeconds();
      }

      //giving player
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
      	//checking if player already has weapon
      	bool hasweapon = false;
      	for (int a = 0; a < player->getWeapons().size(); a++) {
      		if (player->getWeapons()[a].getName() == npc->getWeapons()[selection].getName()) {
      			hasweapon = true;
      			break;
      		}
      	}

      	if (!hasweapon && player->getGold() > npc->getWeapons()[selection].getPrice()) {
      		player->addWeapon(npc->getWeapons()[selection]);
      		player->changeGold(-(npc->getWeapons()[selection].getPrice()));
      		goldText.setString("Gold: " + std::to_string(player->getGold()));
      	}
      }
    }

		window->clear();

		//drawing weapon names
		for (auto weapon : weaponsText) 
			window->draw(weapon);
		window->draw(highlightBar);
		window->draw(messageText);
		window->draw(goldText);
    window->display();
	}
}

void UserInterface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(healthBar[0]);
	target.draw(healthBar[1]);
	target.draw(weaponBox);
	target.draw(*(player->getEquipedWeapon()));
}
