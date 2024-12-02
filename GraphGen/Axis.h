//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"

class Axis
{
public:
	Axis() = default;
	Axis(sf::Vector2i wSize, sf::Font* Roboto);

private:
	sf::RectangleShape axisX;
	sf::RectangleShape axisY;

	std::vector<sf::Text> horizontalScaleTexts;
	std::vector<sf::Text> verticalScaleTexts;
	std::vector<sf::RectangleShape> horizontalScaleRects;
	std::vector<sf::RectangleShape> verticalScaleRects;

	const int offset = 10;
	const sf::Color txtCol = sf::Color(0, 128, 175);
	const sf::Color rectCol = sf::Color(50, 150, 50);

public:
	sf::RectangleShape& GetAxisX() {
		return axisX;
	}

	sf::RectangleShape& GetAxisY() {
		return axisY;
	}

	std::vector<sf::Text>& GetHorizontalScaleTexts() {
		return horizontalScaleTexts;
	};

	std::vector<sf::Text>& GetVerticalScaleTexts() {
		return verticalScaleTexts;
	};

	std::vector<sf::RectangleShape>& GetHorizontalScaleRects() {
		return horizontalScaleRects;
	};

	std::vector<sf::RectangleShape>& GetVerticalScaleRects() {
		return verticalScaleRects;
	};

};

