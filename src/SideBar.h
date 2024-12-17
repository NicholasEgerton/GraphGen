//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"
#include "FunctionInputText.h"

class SideBar : public Widget {
public:
	SideBar() = delete;
	SideBar(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, sf::Color backgroundCol);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual std::vector<Widget*> GetFocusableChildWidgets() override;
private:
	sf::Font& font;
	sf::Color backgroundCol;

	sf::RectangleShape background = sf::RectangleShape(size);
	std::vector<std::unique_ptr<Widget>> childWidgets;
};