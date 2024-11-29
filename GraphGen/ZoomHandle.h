#pragma once

#include "SFML/Graphics.hpp"
#include "Parameters.h"
#include <iostream>

using namespace sf;

namespace ZoomHandle {
	void Zoom(float& precision, float& delta, Parameters* parameters, Text* horizontalScaleTexts, Text* verticalScaleTexts, RenderWindow* window);
	void ZoomScaleTexts(float delta, int precision, Text* horizontalScaleTexts, Text* verticalScaleTexts, RenderWindow* window);
};