#include "Utils.h"

using namespace sf;

Vector2f Utils::LocalToGlobalPos(Vector2f localPos, Vector2f parentPos)
{
	Vector2f globalPos = localPos + parentPos;
	return globalPos;
}

bool Utils::PosInBounds(Vector2f pos, Vector2f boundsPos, Vector2f boundsSize)
{
	if (pos.x >= boundsPos.x && pos.x <= boundsPos.x + boundsSize.x) {
		if (pos.y >= boundsPos.y && pos.y <= boundsPos.y + boundsSize.y) {
			return true;
		}
	}

	return false;
}
