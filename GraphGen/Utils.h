//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"

namespace Utils {
	std::string FloatToString(float f, int precision);
	bool InBounds(sf::Vector2i pointPos, sf::Vector2f boundPos,
		sf::Vector2f boundSize);
	bool IsStringNum(std::string string);
}