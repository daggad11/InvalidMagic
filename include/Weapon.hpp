#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <map>
#include <SFML/Graphics.hpp>

class Weapon : public sf::Drawable {
public:
	enum Type { MELEE, RANGED };
	enum StatName { SPEED, HEALTH, ATTACK, DEFENSE, BASEDAMAGE };

	Weapon();
	Weapon(std::string name, bool type, std::map<int, float> statModifiers, float hitTime, int price, std::string texture);
	std::map<int, float> getStatModifiers();
	float getHitTime();
	bool getType();
	std::string getName();
	int getPrice();
	void setPosition(float x, float y, float width, float height); //setting position in pixels
private:
	sf::Texture texture;
	sf::VertexArray vertices;
	bool type; //type of weapon, melee or ranged
	std::string name; //name of weapon
	std::map<int, float> statModifiers; //modifiers to player stats
	float hitTime; //amount of time between attacks
	int price;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif