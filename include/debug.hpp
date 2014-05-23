#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <SFML/Graphics.hpp>
#include <sstream>

class Debug
{
public:
	Debug();			
	~Debug();
	static void init(sf::RenderWindow* w, sf::View* v);
	static void setString(std::string, int* value);
	//static void setString(std::string, float* value, int line);
	//static void setString(std::string, double* value, int line);
	static void draw();
private:
	static sf::Clock timer;
	static sf::Text text;
	static sf::RenderWindow* window;
	static sf::View* view;
	static std::stringstream stream;
	static std::vector<std::pair<std::string, int*> > pairs; 
};

#endif