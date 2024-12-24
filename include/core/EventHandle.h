//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "core/Renderer.h"
#include "UI/UI.h"

class EventHandle {
public:
	EventHandle() = delete;
	EventHandle(Renderer& renderer, UI& ui) : renderer(renderer), ui(ui) {};
	void Update();
private:
	Renderer& renderer;
	UI& ui;

	sf::Cursor::Type currentCursorType = sf::Cursor::Arrow;
};