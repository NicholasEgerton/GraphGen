//Work of Nicholas Egertons
#pragma once

#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "SideBar.h"

//The UI class manages and draws all parent widgets on the screen,
//And parent widgets may hold their own child widgets that they manage and draw.

class UI {
public:
	UI() = delete;
	UI(Renderer& renderer) : renderer(renderer) {};

	void Update();
private:
	Renderer& renderer;

	SideBar sideBar = SideBar(sf::Vector2f(0, 0), sf::Vector2f(333, 1000), renderer, sf::Color(25, 25, 25));
};