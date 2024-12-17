#include "FunctionInputText.h"
#include <iostream>

using namespace sf;



FunctionInputText::FunctionInputText(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, Color backgroundCol, std::string defaultText, unsigned int charSize) : Widget(pos, size)
{
	text = Text(defaultText, font, charSize);
	text.setPosition(pos);

	background.setPosition(pos);
	background.setFillColor(backgroundCol);
}


void FunctionInputText::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(background);
	target.draw(text);
}

void FunctionInputText::OnClick(sf::Event& event) const
{
	std::cout << "Clicked!\n";
}

std::vector<Widget*> FunctionInputText::GetFocusableChildWidgets()
{
	//FunctionInputText has no child widgets, but itself is focusable.
	return std::vector<Widget*>({ this });
}
