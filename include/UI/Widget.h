//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "core/Renderer.h"
#include "core/EventResult.h"

//Everything drawn to the screen is a child of widget, which itself is a
//Child of sf::Drawable. 

class Widget : public sf::Drawable {
public:
	Widget() = delete;
	Widget(sf::Vector2f pos, sf::Vector2f size) : pos(pos), size(size) {};
	//Note: If a widget has a std::vector<Widget> "childWidgets," it should
	//Be in order from bottom to top, so that in draw(), objects are drawn
	//With correct priority. E.g background before text.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};
	virtual void Update() {};

	virtual EventResult OnEvent(const sf::Event& event) { return { false, sf::Cursor::Arrow }; };

	sf::Vector2f pos;
	sf::Vector2f size;
};