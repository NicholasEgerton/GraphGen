#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;

namespace Utils {
	std::string FloatToString(float f, int precision);
	bool InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize);
	bool IsStringNum(std::string string);
}