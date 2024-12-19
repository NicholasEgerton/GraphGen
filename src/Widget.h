//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "WidgetState.h"

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
	virtual void OnUnfocus(const sf::Event& event) {};

	virtual void OnClick(const sf::Event& event) {};
	virtual sf::Cursor::Type OnHover(const sf::Event& event) { return sf::Cursor::Arrow;  };
	virtual void OnUnhover(const sf::Event& event) {};
	//Note: GetFocusableChildWidgets() should also return itself if it is focusable
	//So that it only requires one function call from parent
	virtual std::vector<Widget*> GetHoverableChildWidgets() { return std::vector<Widget*>(); };

	sf::Vector2f pos;
	sf::Vector2f size;

protected:
	WidgetState state = WidgetState(false, false);

public:
	const WidgetState& GetState() const {
		return state;
	}
};