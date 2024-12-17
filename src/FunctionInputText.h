//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"

class FunctionInputText : public Widget {
public:
	FunctionInputText() = delete;
	FunctionInputText(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, sf::Color backgroundCol, std::string defaultText,
		unsigned int charSize);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void OnClick(sf::Event& event) const override;
	virtual std::vector<Widget*> GetFocusableChildWidgets() override;
private:
	sf::Text text;
	sf::RectangleShape background = sf::RectangleShape(size);
};