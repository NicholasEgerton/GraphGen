#include "core/Renderer.h"
#include <stdexcept>

using namespace sf;

Renderer::Renderer()
{
	//Set the window size to half the resolution
	Vector2u wSize{ VideoMode::getDesktopMode().size };
	wSize.x = (wSize.x + 1) / 2;
	wSize.y = (wSize.y + 1) / 2;
	window = RenderWindow(VideoMode(wSize), "GraphGen");
	//Load fonts
	if (!cambria.openFromFile("resources/fonts/cambria.ttc")) {
		throw std::runtime_error("Failed loading fonts/cambria.ttc");
	}
}

bool Renderer::IsOpen()
{
	return window.isOpen();
}

std::optional<Event> Renderer::PollEvent()
{
	return window.pollEvent();
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
		case Cursor::Type::Arrow:
			window.setMouseCursor(arrowCursor);
			break;
		case Cursor::Type::Text:
			window.setMouseCursor(textCursor);
			break;
	}
}
