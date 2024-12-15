#pragma once

#include "SFML/Graphics.hpp"

namespace Utils {
	sf::Vector2f LocalToGlobalPos(sf::Vector2f localPos, sf::Vector2f parentPos);
}