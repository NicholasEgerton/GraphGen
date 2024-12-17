//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "Widget.h"

//The event handle manages all events
//The important part is the design pattern that all objects that wish
//To be checked to be the focus, are responsible to call AddFocusableWidget(this)

class EventHandle {
public:
	EventHandle() = delete;
	EventHandle(Renderer& renderer) : renderer(renderer) {};
	void Update();
private:
	Renderer& renderer;

	void OnClick(sf::Event& event);
	void CheckForFocus(sf::Event& event);

	std::vector<Widget*> focusableWidgets;
	Widget* focus = nullptr;
public:
	void AddFocusableWidgets(std::vector<Widget*> widgets) {
		focusableWidgets.insert(focusableWidgets.begin(), widgets.begin(), widgets.end());
	}

	void RemoveFocusableWidget(Widget& widget) {
		for (int i = 0; i < focusableWidgets.size(); i++) {
			if (focusableWidgets[i] == &widget) {
				focusableWidgets.erase(focusableWidgets.begin() + i);
			}
		}
	}
};