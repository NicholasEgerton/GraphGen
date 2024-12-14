//Work of Nicholas Egerton
#include "Renderer.h"

using namespace sf;

Renderer::Renderer(std::unique_ptr<RenderWindow> window) : window(std::move(window))
{
	view = std::make_unique<View>(this->window->getDefaultView());
}

void Renderer::Draw(sf::Drawable& obj)
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
