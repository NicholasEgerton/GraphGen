//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "core/Renderer.h"
#include "UI/Widget.h"
#include "core/EventResult.h"

//The UI class manages and draws all parent widgets on the screen,
//And parent widgets may hold their own child widgets that they manage and draw.

class UI {
public:
	UI() = delete;
	UI(Renderer& renderer);

	void Update();
	EventResult OnEvent(sf::Event& event);
private:
	Renderer& renderer;

	std::vector<std::unique_ptr<Widget>> childWidgets;
};