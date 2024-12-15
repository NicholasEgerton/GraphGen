#include "Utils.h"

using namespace sf;

Vector2f Utils::LocalToGlobalPos(Vector2f localPos, Vector2f parentPos)
{
	Vector2f globalPos = localPos + parentPos;
	return globalPos;
}
