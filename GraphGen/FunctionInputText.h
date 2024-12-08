//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "inputText.h"

class FunctionInputText : public InputText {
public:
	FunctionInputText() = default;
	FunctionInputText(sf::Vector2f pos, sf::Vector2f size,
		unsigned int textSize, sf::String defaultText, int maxChar,
		sf::Color textCol, sf::Color backgroundCol, sf::Sprite& iBeam,
		sf::Font& font, sf::RenderWindow& window);

	sf::String ValidText(sf::Event event, sf::String s) override;

private:
	sf::String AddText(sf::String s, char stringToAdd);

	//Received variables
	float charSize{};
};