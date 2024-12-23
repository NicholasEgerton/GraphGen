//Work of Nicholas Egerton
#include "Renderer.h"
#include <assert.h>

using namespace sf;

Renderer::Renderer()
{
	//Setup window and view
	static const VideoMode defaultWindowSize = VideoMode(1000, 1000);
	window = std::make_unique<RenderWindow>(defaultWindowSize, "GraphGen");
	view = std::make_unique<View>(window->getDefaultView());

	//Load fonts
	cambria = std::make_unique<Font>();
	const bool cambriaLoaded = cambria->loadFromFile("fonts/cambria.ttc");
	assert(cambriaLoaded && "Cambria should load from file");

	//Load cursors
	const bool arrowCursorLoaded = arrowCursor.loadFromSystem(Cursor::Arrow);
	assert(arrowCursorLoaded && "ArrowCursor should load from system");

	const bool textCursorLoaded = textCursor.loadFromSystem(Cursor::Text);
	assert(textCursorLoaded && "TextCursor should load from system");
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
