//Work of Nicholas Egerton
#pragma once

#include "inputText.h"
#include "SFML/Graphics.hpp"

class FunctionInputText : public InputText {
public:
	FunctionInputText() = default;
	FunctionInputText(Vector2f pos, Vector2f size, unsigned int textSize, String defaultText, int maxChar, Color textCol, Color backgroundCol, Sprite* iBeam, Font* font, RenderWindow* window);

	String ValidText(Event event, String s) override;

private:
	String AddText(Uint32 text, String s);

	float charSize;
};