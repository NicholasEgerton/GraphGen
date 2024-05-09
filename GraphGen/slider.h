#pragma once

#include "SFML/Graphics.hpp"
#include "inputText.h"

using namespace sf;

class Slider {
public:

	void Init(Vector2f pos, Vector2f size, Color barColor, Color beamColor, float defaultValue, Vector2f valueBounds, bool rounded, InputText* inputText, RenderWindow* window);
	void Update(Event event);
	void Draw();
	void ChangeBeamPos();

	Vector2f valueBounds;

	bool rounded;

private:

	bool InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize);

	float ToValue();

	Vector2f ToBeamPos(float value);

	RectangleShape bar;
	RectangleShape beam;

	bool inControl;

	String inputTextString;

	//Received variables
	RenderWindow* window;

	InputText* inputText;

	float defaultValue;
};