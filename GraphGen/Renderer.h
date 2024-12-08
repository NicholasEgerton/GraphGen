//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Parameters.h"
#include "Axis.h"

class Renderer {
public:
	Renderer() = default;
	Renderer(Parameters& parameters, Axis& axis, sf::RenderWindow& window)
	: parameters(&parameters), axis(&axis), window(&window) {};
	void Update();

private:
	//Received variables
	sf::RenderWindow* window{};
	Parameters* parameters{};
	Axis* axis{};
};