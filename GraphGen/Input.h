//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "ZoomHandle.h"
#include "Axis.h"

class Input {
public:
	Input() = default;
	Input(Parameters& parameters, Axis& axis, sf::RenderWindow& window)
		: parameters(&parameters), axis(&axis), window(&window) {};
	void HandleEvents(sf::Event& event);
	void Update();

private:
	sf::Clock zoomClock = sf::Clock();

	//How many decimal points on the scale
	float precision = 0;

	ZoomHandle::KeyZoom keyZoom = { false, 0 };

	//Received variables
	Parameters* parameters{};
	Axis* axis{};
	sf::RenderWindow* window{};
};