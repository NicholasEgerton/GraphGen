//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

class Button {
public:
	Button() = default;
	Button(Vector2f pos, Vector2f size, Color buttonCol, Color textCol, unsigned int textSize, String defaultText1, String defaultText2, Font* font, RenderWindow* window);
	void Update(Event event);
	void Draw();

private:

	RectangleShape rect;
	Text text;

	bool state = false;

	bool highlight = false;

	//Received variables
	RenderWindow* window;
	String defaultText1;
	String defaultText2;

	Color buttonCol;

public:

	const bool& GetState() {
		return state;
	}
};