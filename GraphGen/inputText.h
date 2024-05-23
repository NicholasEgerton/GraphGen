#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

class InputText {
public:

	virtual void Init(Vector2f pos, Vector2f size, float textSize, String defaultText, int maxChar, Color textCol, Color backgroundCol, Sprite* iBeam, Font* font, RenderWindow* window);
	virtual void Update(Event event);
	void Draw();

	Text text;
	RectangleShape rect;

	int maxChar;

private:

	bool InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize);

	virtual String ValidText(Event event, String s);

	bool inRect = false;
	bool clickedRect = false;

	//Received variables
	RenderWindow* window;
	
	Sprite* iBeam;
};