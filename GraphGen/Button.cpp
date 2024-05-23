#include "Button.h"

void Button::Init(Vector2f pos, Vector2f size, Color buttonCol, Color textCol, float textSize, String defaultText1, String defaultText2, Font* font, RenderWindow* window)
{
	//Setup received variables
	Button::window = window;
	Button::buttonCol = buttonCol;
	Button::defaultText1 = defaultText1;
	Button::defaultText2 = defaultText2;

	//Setup rect and text
	rect = RectangleShape(size);
	rect.setPosition(pos);
	rect.setFillColor(buttonCol);

	text = Text(defaultText1, *font, textSize);
	text.setPosition(Vector2f(pos.x, pos.y - 5));
	text.setFillColor(textCol);
}

void Button::Update(Event event)
{
	//Highlift if mouse is over button
	highlight = InBounds(Mouse::getPosition(*window), rect.getPosition(), rect.getSize());

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


bool Button::InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize)
{
	//Keeping in mind that the position of a rectangle is defined by its top left corner,
	//And the size increases from the top left corner
	//Checking if the point is > than the position and less than the size of the rect + position
	//Gives if the point is in the rect
	if (pointPos.x >= boundPos.x && pointPos.y >= boundPos.y) {
		if (pointPos.x <= boundPos.x + boundSize.x && pointPos.y <= boundPos.y + boundSize.y) {
			return true;
		}
	}

	return false;
}

void Button::Draw()
{
	window->draw(rect);
	window->draw(text);
}

