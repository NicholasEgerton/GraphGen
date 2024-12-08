//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "inputText.h"

class Slider {
public:
	Slider() = default;
	Slider(sf::Vector2f pos, sf::Vector2f size, sf::Color barColor,
		sf::Color beamColor, float defaultValue, sf::Vector2f valueBounds,
		bool rounded, InputText& inputText, sf::RenderWindow& window);
	void Update(sf::Event event);
	void Draw();
	void ChangeBeamPos();

private:

	float ToValue();

	sf::Vector2f ToBeamPos(float value);

	sf::RectangleShape bar;
	sf::RectangleShape beam;

	bool inControl = false;

	bool rounded = false;

	sf::String inputTextString;

	sf::Vector2f valueBounds;

	//Received variables
	sf::RenderWindow* window{};

	InputText* inputText{};

	float defaultValue = 0;

public:

	const bool& GetRounded() {
		return rounded;
	}

	void SetRounded(bool r) {
		rounded = r;
	}

	const sf::Vector2f& GetValueBounds() {
		return valueBounds;
	}

	void SetValueBounds(sf::Vector2f v) {
		valueBounds = v;
	}
};