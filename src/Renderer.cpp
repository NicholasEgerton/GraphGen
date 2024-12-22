//Work of Nicholas Egerton
#include "Renderer.h"
#include <iostream>

using namespace sf;

Renderer::Renderer()
{
	//Setup window and view
	static const VideoMode defaultWindowSize = VideoMode(1000, 1000);
	window = std::make_unique<RenderWindow>(defaultWindowSize, "GraphGen");
	view = std::make_unique<View>(window->getDefaultView());

	//Load fonts
	cambria = std::make_unique<Font>();
	if (!cambria->loadFromFile("fonts/cambria.ttc")) {
		std::cout << "(Renderer) Error: Failed loading font 'fonts/cambria.ttc'\n";
	}

	//Load cursors
	if (!arrowCursor.loadFromSystem(Cursor::Arrow)) {
		std::cout << "(EventHandle) Error: Failed loading arrowCursor\n";
	}
	if (!textCursor.loadFromSystem(Cursor::Text)) {
		std::cout << "(EventHandle) Error: Failed loading textCursor\n";
	}
}

void Renderer::Draw(const Drawable& obj)
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

void Renderer::Resize(const Vector2f newSize)
{
	view->setSize(newSize);
	window->setView(*view);
}

void Renderer::SetCursor(const Cursor::Type cursorType)
{
	switch (cursorType) {
		case Cursor::Arrow:
			window->setMouseCursor(arrowCursor);
			break;
		case Cursor::Text:
			window->setMouseCursor(textCursor);
			break;
	}
}
