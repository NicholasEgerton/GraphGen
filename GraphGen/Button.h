#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

class Button {
public:

	Button() {}
	Button(Vector2f pos, Vector2f size, Color buttonCol, Color textCol, unsigned int textSize, String defaultText1, String defaultText2, Font* font, RenderWindow* window);
	void Update(Event event);
	void Draw();

private:

	bool InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize);

	RectangleShape rect{};
	Text text{};

	String defaultText1{};
	String defaultText2{};

	Color buttonCol{};

	bool state = false;

	bool highlight = false;

	//Received variables
	RenderWindow* window{};

public:

	const bool& GetState() {
		return state;
	}
};