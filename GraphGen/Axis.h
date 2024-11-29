#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

class Axis
{
public:
	Axis(){}
	Axis(Vector2i wSize, Font* Roboto);

private:
	RectangleShape axisX;
	RectangleShape axisY;

	std::vector<Text> horizontalScaleTexts;
	std::vector<Text> verticalScaleTexts;
	std::vector<RectangleShape> horizontalScaleRects;
	std::vector<RectangleShape> verticalScaleRects;

	const int offset = 10;
	const Color txtCol = Color(0, 128, 175);
	const Color rectCol = Color(50, 150, 50);

public:
	RectangleShape& GetAxisX() {
		return axisX;
	}

	RectangleShape& GetAxisY() {
		return axisY;
	}

	std::vector<Text>& GetHorizontalScaleTexts() {
		return horizontalScaleTexts;
	};

	std::vector<Text>& GetVerticalScaleTexts() {
		return verticalScaleTexts;
	};

	std::vector<RectangleShape>& GetHorizontalScaleRects() {
		return horizontalScaleRects;
	};

	std::vector<RectangleShape>& GetVerticalScaleRects() {
		return verticalScaleRects;
	};

};

