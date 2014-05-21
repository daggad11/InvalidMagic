
#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <SFML/Graphics.hpp>
#include <sstream>

class Debug
{
public:
	Debug();				
	Debug(sf::RenderWindow* window);
	~Debug();
	void setString(std::string, int* value, int line);
	void setString(std::string, float* value, int line);
	void setString(std::string, double* value, int line);
private:
	sf::Text text;
	std::vector<std::string> strings;
	sf::RenderWindow* window;
	std::stringstream stream;
};