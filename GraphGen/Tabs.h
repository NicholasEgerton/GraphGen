//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "inputText.h"
#include "slider.h"
#include <sstream>
#include <iostream>

using namespace sf;

class Tabs {
public:

	Tabs() {}
	Tabs(Vector2f pos, Vector2f size, int amount, Color tabCol, Color textCol, unsigned int textSize, Font* font, InputText* aInputText, InputText* nInputText, InputText* cInputText, Slider* aSlider, Slider* nSlider, Slider* cSlider, RenderWindow* window);
	
	void Update(Event event);
	void Draw();

private:

	bool IsNum(std::string string);

	void UpdateValues(int i);

	void UpdateText(int i);

	struct Tab {
		RectangleShape rect;
		Text text;
		bool clicked;
		float a; //Note, these are made strings as 
		float n; //They never are needed in mathematical operations
		float c; //And only interacting with the inputTexts.
	};

	std::vector<Tab> tabs{};

	int tabsAmount{};

	//Received variables
	RenderWindow* window{};

	Vector2f originalSize{};

	Color originalColor{};

	InputText* aInputText{};
	InputText* nInputText{};
	InputText* cInputText{};

	Slider* aSlider{};
	Slider* nSlider{};
	Slider* cSlider{};

public:

	const std::vector<Tab>& GetTabs() {
		return tabs;
	}

	const int& GetTabsAmount() {
		return tabsAmount;
	}

};