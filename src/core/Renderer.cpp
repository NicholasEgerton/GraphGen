//Work of Nicholas Egerton
#include "core/Renderer.h"
#include <stdexcept>

using namespace sf;

const Vector2u Renderer::defaultWindowSize = { 1920, 1080 };

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

void Renderer::Draw(const Drawable& obj)
{
	window.draw(obj);
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

void Renderer::Resize(Vector2u newSize)
{
	static const Vector2u minWindowSize{ 960, 540 };
	static const Vector2u maxWindowSize{ 1920, 1080 };

	//Clamp newSize in range
	newSize.x = std::max(minWindowSize.x, std::min(newSize.x, maxWindowSize.x));
	newSize.y = std::max(minWindowSize.y, std::min(newSize.y, maxWindowSize.y));

	//Resize the view
	if (window.getSize() != newSize) {
		window.setSize(newSize);
	}
	window.setSize(newSize);
	view.setSize(Vector2f(newSize));
	view.setCenter(Vector2f(newSize.x / 2.f, newSize.y / 2.f));
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
