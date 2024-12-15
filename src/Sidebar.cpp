//Work of Nicholas Egerton
#include "SideBar.h"

using namespace sf;

SideBar::SideBar(sf::Vector2f pos, sf::Vector2f size, Renderer& renderer, sf::Color backgroundCol) : Widget(pos, size, renderer), backgroundCol(backgroundCol)
{
	sideBarShape.setPosition(pos);
	sideBarShape.setFillColor(backgroundCol);
}

void SideBar::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(sideBarShape, states);
	functionInputText.draw(target, states);
}
