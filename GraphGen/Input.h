#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include "ZoomHandle.h"
#include "Axis.h"

class Input {
public:
	Input(Parameters& parameters, Axis& axis, RenderWindow& window)
		: parameters(parameters), axis(axis), window(window) {};
	void HandleEvents(Event& event);
	void Update();

private:
	Clock zoomClock = Clock();

	//How many decimal points on the scale
	float precision = 0;

	ZoomHandle::KeyZoom keyZoom = { false, 0 };

	//Received variables
	Parameters& parameters;
	Axis& axis;
	RenderWindow& window;
};