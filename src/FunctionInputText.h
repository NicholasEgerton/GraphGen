//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"

class FunctionInputText : public Widget {
public:
	FunctionInputText() = delete;
	FunctionInputText(sf::Vector2f pos, sf::Vector2f size, Renderer& renderer, std::string defaultText,
		unsigned int charSize);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	const std::string defaultText;
	int charSize;

	sf::Text text = sf::Text(defaultText, *renderer.GetCambria(), charSize);
};