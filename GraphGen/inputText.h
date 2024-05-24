#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

class InputText {
public:

	InputText() {}
	InputText(Vector2f pos, Vector2f size, unsigned int textSize, String defaultText, int maxChar, Color textCol, Color backgroundCol, Sprite* iBeam, Font* font, RenderWindow* window);
	virtual void Update(Event event);
	void Draw();

protected:


	Text text{};
	RectangleShape rect{};

	int maxChar{};

private:
	virtual String ValidText(Event event, String s);

	bool InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize);


	bool inRect = false;
	bool clickedRect = false;


	//Received variables
	RenderWindow* window{};

	Sprite* iBeam{};

public:

	const Text& GetText() {
		return text;
	}

	void SetTextString(String s) {
		text.setString(s);
	}

	const int& GetMaxChar() {
		return maxChar;
	}
};