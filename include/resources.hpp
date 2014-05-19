#ifndef RESOURCES_HPP
#define RESOURCES_HPP
#include <SFML/Graphics.hpp>
#include <map>

class Resources {
	public:
		Resources();
		~Resources();
		static void init();
		static sf::Texture* getTexture(std::string texture);
	private:
		static std::map<std::string, sf::Texture> textures;
};

#endif
