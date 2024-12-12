//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "inputText.h"
#include "slider.h"

using namespace sf;

class Tabs {
public:
	Tabs() = default;
	Tabs(sf::Vector2f pos, sf::Vector2f size, int amount, sf::Color tabCol,
		sf::Color textCol, unsigned int textSize, sf::Font& font, 
		InputText& aInputText, InputText& nInputText, InputText& cInputText,
		Slider& aSlider, Slider& nSlider, Slider& cSlider,
		sf::RenderWindow& window);
	
	void Update(Event event);
	void Draw();

	struct Tab {
		sf::RectangleShape rect;
		sf::Text text;
		bool clicked;
		float a; //Note, these are made strings as 
		float n; //They never are needed in mathematical operations
		float c; //And only interacting with the inputTexts.
	};

private:
	void UpdateValues(int i);

	void UpdateText(int i);

	std::vector<Tab> tabs;

	int tabsAmount;

	//Received variables
	sf::RenderWindow* window{};

	sf::Vector2f originalSize{};

	sf::Color originalColor{};

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