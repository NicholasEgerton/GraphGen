//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Parameters.h"

namespace ZoomHandle {
	void Zoom(float& precision, float& delta, Parameters* parameters,
		std::vector<sf::Text>& horizontalScaleTexts,
		std::vector<sf::Text>& verticalScaleTexts, sf::RenderWindow* window);
	void ZoomScaleTexts(float delta, int precision,
		std::vector<sf::Text>& horizontalScaleTexts,
		std::vector<sf::Text>& verticalScaleTexts, sf::RenderWindow* window);

	struct KeyZoom {
		bool zooming;
		float key; //-1 = -, 1 = +
	};
};