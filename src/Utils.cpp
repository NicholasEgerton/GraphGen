#include "Utils.h"

using namespace sf;

Vector2f Utils::LocalToGlobalPos(Vector2f localPos, Vector2f parentPos)
{
	Vector2f globalPos = localPos + parentPos;
	return globalPos;
}

bool Utils::PosInBounds(sf::Vector2f pos, sf::Vector2f boundsPos, sf::Vector2f boundsSize)
{
	if (pos.x >= boundsPos.x && pos.x <= boundsPos.x + boundsSize.x) {
		if (pos.y >= boundsPos.y && pos.y <= boundsPos.y + boundsSize.y) {
			return true;
		}
	}

	return false;
}
