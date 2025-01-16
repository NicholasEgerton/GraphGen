#pragma once

#include "SFML/Graphics.hpp"

namespace Utils {
	sf::Vector2f LocalToGlobalPos(const sf::Vector2f localPos, const sf::Vector2f parentPos);
}