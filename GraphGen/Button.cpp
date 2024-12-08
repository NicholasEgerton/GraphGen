//Work of Nicholas Egerton
#include "Button.h"
#include "Utils.h"

using namespace sf;

Button::Button(Vector2f pos, Vector2f size, Color buttonCol, Color textCol, unsigned int textSize, String defaultText1, String defaultText2, Font& font, RenderWindow& window)
	: buttonCol(buttonCol), defaultText1(defaultText1), defaultText2(defaultText2), window(&window)
{
	//Setup rect and text
	rect = RectangleShape(size);
	rect.setPosition(pos);
	rect.setFillColor(buttonCol);

	text = Text(defaultText1, font, textSize);
	text.setPosition(Vector2f(pos.x, pos.y - 5));
	text.setFillColor(textCol);
}

void Button::Update(Event event)
{
	//Highlift if mouse is over button
	highlight = Utils::InBounds(Mouse::getPosition(*window), rect.getPosition(), rect.getSize());

	//Make even brighter if clicked and switch state
	if (highlight) {
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			state = !state;
			rect.setFillColor(buttonCol + Color(150, 150, 150));
		}
		else {
			rect.setFillColor(buttonCol + Color(100, 100, 100));
		}
	}

	else {
		rect.setFillColor(buttonCol);
	}

	//Change text based on state
	if (!state) {
		if (text.getString() != defaultText1) {
			text.setString(defaultText1);
		}
	}

	else {
		if (text.getString() != defaultText2) {
			text.setString(defaultText2);
		}
	}
}

void Button::Draw()
{
	window->draw(rect);
	window->draw(text);
}

