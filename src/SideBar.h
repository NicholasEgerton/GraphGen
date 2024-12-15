//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"
#include "FunctionInputText.h"
#include "Utils.h"

class SideBar : public Widget {
public:
	SideBar() = delete;
	SideBar(sf::Vector2f pos, sf::Vector2f size, Renderer& renderer, sf::Color backgroundCol);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Color backgroundCol;

	sf::RectangleShape sideBarShape = sf::RectangleShape(size);
	FunctionInputText functionInputText = FunctionInputText(Utils::LocalToGlobalPos(sf::Vector2f(20,10), pos),
		sf::Vector2f(300, 200), renderer, "y = x", 50);
};