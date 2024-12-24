//Work of Nicholas Egerton
#include "InputText.h"
#include "Utils.h"
#include <assert.h>

using namespace sf;

InputText::InputText(Vector2f pos, Vector2f size, Font& font, Color backgroundCol, std::string defaultText, unsigned int charSize) : InputWidget(pos, size), charSize(charSize)
{
	text = Text(defaultText, font, charSize);
	text.setPosition(pos);

	background.setPosition(pos);
	background.setFillColor(backgroundCol);

	caret = RectangleShape(Vector2f(2.f, size.y * 0.90f));
	caret.setPosition(Vector2f(-1.f, pos.y + size.y * 0.05f));
}


void InputText::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(background, states);
	target.draw(text, states);

	if (state.focused) {
		if (showCaret) {
			target.draw(caret);
		}
	}
}

void InputText::Update()
{
	if (state.focused) {
		//Every 0.5 seconds show or hide the caret
		if (caretClock.getElapsedTime().asSeconds() > 0.5f) {
			showCaret = !showCaret;
			caretClock.restart();
		}
	}
}

void InputText::UpdateCaret(Vector2f mousePos)
{
	std::string s{ text.getString() };

	//Note: To get the last character of the string we use an index outside
	//The range of the string, and this is ok as text.findCharacterPos(), 
	//returns the pos at the end of the string if index is out of range.
	if (s.empty()) {
		MoveCaret(0);
		return;
	}

	//We only care about the x value as the height is always the same
	//This is the x displacement of the caret FROM the caret
	float displacement{ FindCaretDisplacement(0, mousePos) };

	if (s.size() == 1) {
		if (displacement > 0) {
			MoveCaret(0);
			return;
		}

		else {
			MoveCaret(1);
			return;
		}
	}

	else if (displacement >= 0) {
		MoveCaret(0);
		return;
	}

	//We start loop from the second character as we don't need
	//To check for the old displacement for the first
	for (size_t i = 1; i < s.size(); ++i) {
		float newDisplacement{ FindCaretDisplacement(i, mousePos) };

		//If the old displacement is negative and the new displacement
		//Is positive that means the caret is between the two
		if (displacement <= 0 && newDisplacement >= 0) {
			MoveCaret(i);
			break;
		}

		else if (i + 1 == s.size()) {
			MoveCaret(i+1);
			break;
		}

		else {
			displacement = newDisplacement;
		}
	}
}

float InputText::FindCaretDisplacement(size_t charIndex, Vector2f mousePos)
{
	float charX{ FindCharacterMiddleX(charIndex) };
	float displacement{ charX - mousePos.x };
	return displacement;
}

float InputText::FindCharacterMiddleX(size_t charIndex)
{
	std::string s{ text.getString() };

	assert(charIndex < s.size() && "charIndex should be in range of string");
	float left{ Utils::GetCharacterPos(text, charIndex).x };
	float middle{ left + (Utils::GetCharacterWidth(s[charIndex], charSize, *text.getFont(), false) / 2.f) };
	return middle;
}

void InputText::MoveCaret(size_t charIndex)
{
	caret.setPosition(Utils::GetCharacterPos(text, charIndex).x, caret.getPosition().y);
}

EventResult InputText::OnHover(const Event& event)
{
	state.hovered = true;
	return { true, Cursor::Text };
}

EventResult InputText::OnUnhover(const Event& event)
{
	state.hovered = false;
	return { true, Cursor::Arrow };
}

EventResult InputText::OnClick(const Event& event)
{
	if (!state.focused) {
		caretClock.restart();
	}
	showCaret = true;
	Vector2f mousePos{ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
	UpdateCaret(mousePos);
	state.focused = true;
	return { false, Cursor::Arrow };
}

EventResult InputText::OnUnfocus(const Event& event)
{
	state.focused = false;
	return { false, Cursor::Arrow };
}
