#ifndef HUD_HPP
#define HUD_HPP
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class HUD : public sf::Drawable {
public:
	HUD(Player* player, sf::View* view, sf::RenderWindow* window);
	void update();
private:
	Player* player;
	sf::View* view;
	sf::RenderWindow* window;

	sf::RectangleShape healthBar[2]; //healthbars for player

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif