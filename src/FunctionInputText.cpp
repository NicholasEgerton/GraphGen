//Work of Nicholas Egerton
#include "FunctionInputText.h"
#include <iostream>

using namespace sf;

FunctionInputText::FunctionInputText(Vector2f pos, Vector2f size, Font& font, Color backgroundCol, std::string defaultText, unsigned int charSize) : Widget(pos, size)
{
	text = Text(defaultText, font, charSize);
	text.setPosition(pos);

	background.setPosition(pos);
	background.setFillColor(backgroundCol);

	const float fCharSize = static_cast<float>(charSize);
	caret = RectangleShape(Vector2f(fCharSize, fCharSize));
}


void FunctionInputText::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(background, states);
	target.draw(text, states);
}

void FunctionInputText::Update()
{
	std::cout << "Focused = " << state.focused << "Hovered = " << state.hovered << '\n';
}


Cursor::Type FunctionInputText::OnHover(const Event& event)
{
	state.hovered = true;
	return Cursor::Text;
}

void FunctionInputText::OnUnhover(const Event& event)
{
	state.hovered = false;
}

void FunctionInputText::OnClick(const Event& event)
{
	state.focused = true;
}

void FunctionInputText::OnUnfocus(const Event& event)
{
	state.focused = false;
}

std::vector<Widget*> FunctionInputText::GetHoverableChildWidgets()
{
	//FunctionInputText has no child widgets, but itself is hoverable.
	return std::vector<Widget*>({ this });
}
