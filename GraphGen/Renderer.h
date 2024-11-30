//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Parameters.h"
#include "Axis.h"
#include <iostream>

using namespace sf;

class Renderer {
public:
	Renderer(Parameters& parameters, Axis& axis, RenderWindow& window)
	: parameters(parameters), axis(axis), window(window) {};
	void Update();

private:
	//Received variables
	RenderWindow& window;
	Parameters& parameters;
	Axis& axis;
};