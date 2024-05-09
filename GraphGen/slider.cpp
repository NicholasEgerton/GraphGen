#include "slider.h"

void Slider::Init(Vector2f pos, Vector2f size, Color barColor, Color beamColor, float defaultValue, Vector2f valueBounds, bool rounded, InputText* inputText, RenderWindow* window)
{
	//Setup received variables
	Slider::window = window;
	Slider::inputText = inputText;
	Slider::defaultValue = defaultValue;
	Slider::valueBounds = valueBounds;
	Slider::rounded = rounded;

	inputTextString = inputText->text.getString();

	//Setup bar and beam
	bar = RectangleShape(size);
	bar.setPosition(pos);
	bar.setFillColor(barColor);

	beam = RectangleShape(Vector2f(size.y, size.x / 6));
	beam.setPosition(Vector2f(pos.x, pos.y - size.y));
	beam.setFillColor(beamColor);

	beam.setPosition(ToBeamPos(defaultValue));
}

void Slider::Update(Event event)
{

	//Check if mouse is on beam
	if (InBounds(Mouse::getPosition(*window), beam.getPosition(), beam.getSize()) && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		inControl = true;
	}

	else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
		inControl = false;
	}

	//Check if mouse is within the bounds of bar
	//(Stop the beam from coming of bar)
	//Note, allowing the mouse to be at any y value, but has to be on x of bar
	//More fluid movement
	if (inControl && InBounds(Mouse::getPosition(*window), Vector2f(bar.getPosition().x, 0), Vector2f(bar.getSize().x, 500))) {
		beam.setPosition(Vector2f(Mouse::getPosition(*window).x, beam.getPosition().y));
		
		if (rounded) {
			int value = round(ToValue());
			inputText->text.setString(std::to_string(value));
		}

		else {
			float value = roundf(ToValue() * 1000000) / 1000000;
			inputText->text.setString(std::to_string(value));
		}
	}
}

float Slider::ToValue()
{
	//Convert the position of the beam on the bar to the value within the bounds

	//Value = lower Bounds + (2 * upper Bounds * ratio)
	//ratio of beam to bar = local beam pos / bar distance

	float dist = bar.getSize().x;

	float localPos = beam.getPosition().x - bar.getPosition().x;

	float ratio = localPos / dist;

	float value = valueBounds.x + (2 * valueBounds.y * ratio);

	return value;
}

Vector2f Slider::ToBeamPos(float value)
{
	float dist = bar.getSize().x;

	float ratio = (value - valueBounds.x) / 2 / valueBounds.y;

	float localPos = ratio * dist;

	float pos = localPos + bar.getPosition().x;

	return Vector2f(pos, beam.getPosition().y);
}

bool Slider::InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize)
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

void Slider::Draw()
{
	window->draw(bar);
	window->draw(beam);
}

void Slider::ChangeBeamPos()
{
	//Update slider if user changes input text
	std::string s = inputText->text.getString();

	float f = std::stof(s);

	if (f < valueBounds.x) {
		beam.setPosition(ToBeamPos(valueBounds.x));
	}

	else if (f > valueBounds.y) {
		beam.setPosition(ToBeamPos(valueBounds.y));
	}

	else {
		beam.setPosition(ToBeamPos(f));
	}
}
