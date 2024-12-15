//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Renderer.h"

class Widget : public sf::Drawable {
public:
	Widget() = delete;
	Widget(sf::Vector2f pos, sf::Vector2f size, Renderer& renderer) : pos(pos), size(size), renderer(renderer) {};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};
protected:
	sf::Vector2f pos;
	sf::Vector2f size;
	Renderer& renderer;
};