#pragma once

#include "SFML/Graphics.hpp"

struct EventResult {
	bool consumeInput;
	sf::Cursor::Type newCursorType;
};