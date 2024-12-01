//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "inputText.h"

using namespace sf;

class Slider {
public:
	Slider() = default;
	Slider(Vector2f pos, Vector2f size, Color barColor, Color beamColor, float defaultValue, Vector2f valueBounds, bool rounded, InputText* inputText, RenderWindow* window);
	void Update(Event event);
	void Draw();
	void ChangeBeamPos();

private:

	float ToValue();

	Vector2f ToBeamPos(float value);

	RectangleShape bar;
	RectangleShape beam;

	bool inControl = false;

	bool rounded = false;

	String inputTextString;

	Vector2f valueBounds;

	//Received variables
	RenderWindow* window;

	InputText* inputText;

	float defaultValue = 0;

public:

	const bool& GetRounded() {
		return rounded;
	}

	void SetRounded(bool r) {
		rounded = r;
	}

	const Vector2f& GetValueBounds() {
		return valueBounds;
	}

	void SetValueBounds(Vector2f v) {
		valueBounds = v;
	}
};