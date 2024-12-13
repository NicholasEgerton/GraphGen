//Work of Nicholas Egerton
#include "Renderer.h"

using namespace sf;

Renderer::Renderer(std::unique_ptr<RenderWindow> window) : window(std::move(window))
{
	view = std::make_unique<View>(Renderer::window->getDefaultView());
}

void Renderer::Update()
{
	window->clear();

	window->display();
}
