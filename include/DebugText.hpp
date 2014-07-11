#ifndef DEBUG_TEXT
#define DEBUG_TEXT
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

/*DebugText stores strings in a specified number of lines
to be drawn onto the screen. The position, font size, and font color
of these strings can be changed all at once. The text for each
line can be changed individually.*/

class DebugText : public sf::Drawable {
public:
	DebugText(int lines); //constructor passes in number of lines of text
	void setLine(int line, std::string string); //sets text of specific line
	void setPosition(sf::Vector2f position); //sets position of text
private:
	int lines; //number of lines to be drawn
	std::vector<std::string> strings; //actual lines of text
	sf::Font font; //font for text
	sf::Text text; //text that will be drawn to screen

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //allows text to be drawn by window
};

#endif