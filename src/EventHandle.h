//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "Widget.h"

//The event handle manages all events
//The important part is the design pattern that all objects that wish
//To be checked to be hovered, are responsible to call AddHoverableWidget(this)

class EventHandle {
public:
	EventHandle() = delete;
	EventHandle(Renderer& renderer);
	void Update();
private:
	Renderer& renderer;

	void OnClick(sf::Event& event);
	void CheckForHover(sf::Event& event);

	std::vector<Widget*> hoverableWidgets;
	Widget* hover = nullptr;
	Widget* focus = nullptr;

	sf::Cursor arrowCursor;
	sf::Cursor textCursor;
	sf::Cursor::Type currentCursorType;
public:
	void AddHoverableWidgets(std::vector<Widget*> widgets) {
		hoverableWidgets.insert(hoverableWidgets.begin(), widgets.begin(), widgets.end());
	}
};