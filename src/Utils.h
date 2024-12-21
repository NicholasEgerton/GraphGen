#pragma once

#include "SFML/Graphics.hpp"

namespace Utils {
	sf::Vector2f LocalToGlobalPos(const sf::Vector2f localPos, const sf::Vector2f parentPos);
	sf::Vector2f GetCharacterPos(const sf::Text& text, const size_t charIndex);
	float GetCharacterWidth(const char& c, const unsigned int charSize, const sf::Font& font, const bool bold);
	bool PosInBounds(const sf::Vector2f pos, const sf::Vector2f boundsPos, const sf::Vector2f boundsSize);
}