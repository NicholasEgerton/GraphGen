#include "core/Utils.h"

using namespace sf;

Vector2f Utils::LocalToGlobalPos(const Vector2f localPos, const Vector2f parentPos)
{
	return localPos + parentPos;
}