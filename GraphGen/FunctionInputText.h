#pragma once

#include "inputText.h"
#include "SFML/Graphics.hpp"

class FunctionInputText : public InputText {
public:

	void Init(Vector2f pos, Vector2f size, float textSize, String defaultText, int maxChar, Color textCol, Color backgroundCol, Sprite* iBeam, Font* font, RenderWindow* window) override;

	String ValidText(Event event, String s) override;

private:
	String AddText(Uint32 text, String s);

	float charSize;
};