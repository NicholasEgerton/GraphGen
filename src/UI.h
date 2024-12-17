//Work of Nicholas Egertons
#pragma once

#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "EventHandle.h"
#include "Widget.h"

//The UI class manages and draws all parent widgets on the screen,
//And parent widgets may hold their own child widgets that they manage and draw.

class UI {
public:
	UI() = delete;
	UI(Renderer& renderer, EventHandle& eventHandle);

	void Update();
private:
	Renderer& renderer;
	EventHandle& eventHandle;

	std::vector<std::unique_ptr<Widget>> childWidgets;
};