//Work of Nicholas Egerton
#include "Renderer.h"
#include <iostream>

using namespace sf;

Renderer::Renderer()
{
	static const VideoMode defaultWindowSize = VideoMode(1000, 1000);
	window = std::make_unique<RenderWindow>(defaultWindowSize, "GraphGen");
	view = std::make_unique<View>(window->getDefaultView());
	cambria = std::make_unique<Font>();
	if (!cambria->loadFromFile("fonts/cambria.ttc")) {
		std::cout << "(Renderer) Error: Failed loading font 'fonts/cambria.ttc'\n";
	}
}

void Renderer::Draw(Drawable& obj)
{
	window->draw(obj);
}

void Renderer::Display()
{
	window->display();
}

void Renderer::Clear()
{
	window->clear();
}

void Renderer::Close()
{
	window->close();
}

void Renderer::Resize(Vector2f newSize)
{
	view->setSize(newSize);
	window->setView(*view);
}
