#include "FunctionInputText.h"

using namespace sf;



FunctionInputText::FunctionInputText(sf::Vector2f pos, sf::Vector2f size, Renderer& renderer, std::string defaultText, unsigned int charSize) : Widget(pos, size, renderer), defaultText(defaultText), charSize(charSize)
{
	text.setPosition(pos);
}


void FunctionInputText::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(text, states);
}
