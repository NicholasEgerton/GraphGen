//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Renderer.h"

class EventHandle {
public:
	EventHandle() = delete;
	EventHandle(Renderer& renderer) : renderer(renderer) {};
	void Update();

private:
	Renderer& renderer;
};