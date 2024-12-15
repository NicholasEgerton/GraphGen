//Work of Nicholas Egerton
#include "UI.h"
#include <iostream>

using namespace sf;



UI::UI(Renderer& renderer) : renderer(renderer)
{
	if (!this->renderer.GetCambria()->loadFromFile("fonts/cambria.ttc")) {
		std::cout << "(UI) Error: Failed loading font cambria" << std::endl;
	}
}

void UI::Update()
{
	renderer.Draw(sideBar);
}
