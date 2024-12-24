//Work of Nicholas Egerton
#include "core/Renderer.h"
#include <stdexcept>

using namespace sf;

Renderer::Renderer()
{
	//Setup window and view
	window = std::make_unique<RenderWindow>(VideoMode(defaultWindowSize.x, defaultWindowSize.y), "GraphGen");
	view = std::make_unique<View>(window->getDefaultView());

	//Load fonts
	cambria = std::make_unique<Font>();
	if (!cambria->loadFromFile("fonts/cambria.ttc")) {
		throw std::runtime_error("Failed loading fonts/cambria.ttc");
	}

	//Load cursors
	if (!arrowCursor.loadFromSystem(Cursor::Arrow)) {
		throw std::runtime_error("Failed loading Cursor::Arrow from system");
	}

	if (!textCursor.loadFromSystem(Cursor::Text)) {
		throw std::runtime_error("Failed loading Cursor::Text from system");
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

void Renderer::Resize(const Vector2u newSize)
{
	//Make sure newSize is within min and max window size
	if (newSize.x < minWindowSize.x) {
		window->setSize(Vector2u(minWindowSize.x, window->getSize().y));
		return;
	}

	else if (newSize.x > maxWindowSize.x) {
		window->setSize(Vector2u(maxWindowSize.x, window->getSize().y));
		return;
	}

	else if (newSize.y < minWindowSize.y) {
		window->setSize(Vector2u(window->getSize().x, minWindowSize.y));
		return;
	}

	else if (newSize.y > maxWindowSize.y) {
		window->setSize(Vector2u(window->getSize().x, maxWindowSize.y));
		return;
	}

	//If the newSize is valid, resize the view
	view->setSize(Vector2f(newSize));
	view->setCenter(Vector2f(newSize.x / 2.f, newSize.y / 2.f));
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
