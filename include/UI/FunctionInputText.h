//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "UI/InputText.h"

class FunctionInputText : public InputText {
public:
	FunctionInputText(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, sf::Color backgroundCol, std::string defaultText,
		unsigned int charSize) : InputText(pos, size, font, backgroundCol, defaultText, charSize){};
};