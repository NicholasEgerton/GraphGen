#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

class InputText {
public:

	void Init(Vector2f pos, Vector2f size, float textSize, String defaultText, int maxChar, Color textCol, Color backgroundCol, Sprite* iBeam, Font* font, RenderWindow* window);
	void Update(Event event);
	void Draw();

	Text text;
	RectangleShape rect;

private:

	bool inRect = false;
	bool clickedRect = false;

	bool InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize);

	//Received variables
	RenderWindow* window;
	
	Sprite* iBeam;

	int maxChar;
};