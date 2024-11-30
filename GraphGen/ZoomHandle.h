#pragma once

#include "SFML/Graphics.hpp"
#include "Parameters.h"
#include <iostream>

using namespace sf;

namespace ZoomHandle {
	void Zoom(float& precision, float& delta, Parameters* parameters, std::vector<Text>& horizontalScaleTexts, std::vector<Text>& verticalScaleTexts, RenderWindow* window);
	void ZoomScaleTexts(float delta, int precision, std::vector<Text>& horizontalScaleTexts, std::vector<Text>& verticalScaleTexts, RenderWindow* window);

	struct KeyZoom {
		bool zooming;
		float key; //-1 = -, 1 = +
	};
};