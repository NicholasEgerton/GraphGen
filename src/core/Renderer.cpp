//Work of Nicholas Egerton
#include "core/Renderer.h"
#include <stdexcept>

using namespace sf;

Renderer::Renderer()
{
	//Load fonts
	if (!cambria.loadFromFile("fonts/cambria.ttc")) {
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

bool Renderer::IsOpen()
{
	return window.isOpen();
}

bool Renderer::PollEvent(Event& event)
{
	return window.pollEvent(event);
}

void Renderer::Draw(const Drawable& obj, const RenderStates states)
{
	window.draw(obj, states);
}

void Renderer::Display()
{
	window.display();
}

void Renderer::Clear(const Color color)
{
	window.clear(color);
}

void Renderer::Close()
{
	window.close();
}

void Renderer::SetView(const sf::View& view)
{
	window.setView(view);
}

void Renderer::SetCursor(const Cursor::Type cursorType)
{
	switch (cursorType) {
		case Cursor::Arrow:
			window.setMouseCursor(arrowCursor);
			break;
		case Cursor::Text:
			window.setMouseCursor(textCursor);
			break;
	}
}
