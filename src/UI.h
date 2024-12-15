//Work of Nicholas Egertons
#pragma once

#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "SideBar.h"

class UI {
public:
	UI() = delete;
	UI(Renderer& renderer);

	void Update();
private:
	Renderer& renderer;

	SideBar sideBar = SideBar(sf::Vector2f(0, 0), sf::Vector2f(333, 1000), renderer, sf::Color(25, 25, 25));
};