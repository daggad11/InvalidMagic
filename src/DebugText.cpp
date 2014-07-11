#include "DebugText.hpp"
#include <iostream>

/////////////////////
//PUBLIC FUNCTIONS//
////////////////////

DebugText::DebugText(int lines) {
	this->lines = lines;

	//pushing back blank lines into vector
	for(int a = 0; a < lines; a++) {
		strings.push_back("");
	}

	//loading default font for sf text
	font.loadFromFile("resources/stocky.ttf");

	//setting defaults for text 
	text.setCharacterSize(20);
	text.setFont(font);
	text.setString("");
	text.setPosition(0, 0);
}

void DebugText::setLine(int line, std::string string) {
	strings[line] = string;

	//combining all lines into one string for sf::text
	std::string allLines = "";
	for (int a = 0; a < strings.size(); a++) {
		allLines += strings[a] + "\n";
	}

	//puting combined string into text
	text.setString(allLines);
}

void DebugText::setPosition(sf::Vector2f position) {
	text.setPosition(position);
}

/////////////////////
//PRIVATE FUNCTIONS//
/////////////////////

void DebugText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(text, states);
}