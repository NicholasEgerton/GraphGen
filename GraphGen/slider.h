#pragma once

#include "SFML/Graphics.hpp"
#include "inputText.h"

using namespace sf;

class Slider {
public:

	void Init(Vector2f pos, Vector2f size, Color barColor, Color beamColor, Vector2f valueBounds, bool rounded, InputText* inputText, RenderWindow* window);
	void Update(Event event);
	void Draw();

	Vector2f valueBounds;

	bool rounded;

private:

	bool InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize);

	float toValue();

	RectangleShape bar;
	RectangleShape beam;

	bool inControl;

	//Received variables
	RenderWindow* window;

	InputText* inputText;
};