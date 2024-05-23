#pragma once

#include "SFML/Graphics.hpp"
#include "inputText.h"
#include "slider.h"
#include <sstream>
#include <iostream>

using namespace sf;

class Tabs {
public:

	void Init(Vector2f pos, Vector2f size, int amount, Color tabCol, Color textCol, float textSize, Font* font, InputText* aInputText, InputText* nInputText, InputText* cInputText, Slider* aSlider, Slider* nSlider, Slider* cSlider, RenderWindow* window);
	void Update(Event event);
	void Draw();

	struct Tab {
		RectangleShape rect;
		Text text;
		bool clicked;
		float a; //Note, these are made strings as 
		float n; //They never are needed in mathematical operations
		float c; //And only interacting with the inputTexts.
	};

	std::vector<Tab> tabs;

	int tabsAmount;

private:

	bool hovered;

	bool InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize);

	bool IsNum(std::string string);

	std::string FloatToString(float f, int precision);

	void UpdateValues(int i);

	void UpdateText(int i);

	//Received variables
	RenderWindow* window;

	Vector2f originalSize;

	Color originalColor;

	InputText* aInputText;
	InputText* nInputText;
	InputText* cInputText;

	Slider* aSlider;
	Slider* nSlider;
	Slider* cSlider;
};