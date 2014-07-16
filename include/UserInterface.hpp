#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class UserInterface : public sf::Drawable {
public:
	UserInterface(Player* player, sf::View* view, sf::RenderWindow* window);
	void update();
	void weaponsMenu();
private:
	Player* player;
	sf::View* view;
	sf::RenderWindow* window;

	sf::RectangleShape healthBar[2]; //healthbars for player

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
