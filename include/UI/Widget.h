//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "core/Renderer.h"
#include "core/EventResult.h"

//Everything drawn to the screen is a child of widget, which itself is a
//Child of sf::Drawable and sf::Transformable. 

class Widget : public sf::Drawable, public sf::Transformable {
public:
	Widget() = delete;
	Widget(const sf::Vector2f pos, const sf::Vector2f size) : size(size) { setPosition(pos); };
	//Note: If a widget has a std::vector<Widget> "childWidgets," it should
	//Be in order from bottom to top, so that in draw(), objects are drawn
	//With correct priority. E.g background before text.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};
	virtual void Update() {};

	virtual EventResult OnEvent(const std::optional<sf::Event>& event) { return { false, sf::Cursor::Type::Arrow }; };

protected:
	sf::Vector2f size;

public:
	const sf::Vector2f& GetSize() const {
		return size;
	}
};