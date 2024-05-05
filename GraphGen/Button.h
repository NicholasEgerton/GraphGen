#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

class Button {
public:

	void Init(Vector2f pos, Vector2f size, Color buttonCol, Color textCol, float textSize, String defaultText1, String defaultText2, Font* font, RenderWindow* window);
	void Update(Event event);
	void Draw();

	bool state;

private:

	bool InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize);

	RectangleShape rect;
	Text text;

	String defaultText1;
	String defaultText2;

	Color buttonCol;

	bool highlight;

	//Received variables
	RenderWindow* window;
};