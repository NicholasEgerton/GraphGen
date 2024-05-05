#include "slider.h"

void Slider::Init(Vector2f pos, Vector2f size, Color barColor, Color beamColor, Vector2f valueBounds, bool rounded, InputText* inputText, RenderWindow* window)
{
	//Setup received variables
	Slider::window = window;
	Slider::inputText = inputText;
	Slider::valueBounds = valueBounds;
	Slider::rounded = rounded;

	//Setup bar and beam
	bar = RectangleShape(size);
	bar.setPosition(pos);
	bar.setFillColor(barColor);

	beam = RectangleShape(Vector2f(size.y, size.x / 6));
	beam.setPosition(Vector2f(pos.x, pos.y - size.y));
	beam.setFillColor(beamColor);
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
			int value = round(toValue());
			inputText->text.setString(std::to_string(value));
		}

		else {
			float value = roundf(toValue() * 1000000) / 1000000;
			inputText->text.setString(std::to_string(value));
		}
	}
}

float Slider::toValue()
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
