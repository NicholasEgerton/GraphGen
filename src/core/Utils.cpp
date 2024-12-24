#include "core/Utils.h"

using namespace sf;

Vector2f Utils::LocalToGlobalPos(const Vector2f localPos, const Vector2f parentPos)
{
	return localPos + parentPos;
}

Vector2f Utils::GetCharacterPos(const Text& text, const size_t charIndex)
{
	//We want to get the top left of the character, but
	//findCharacterPos returns the left edge of the character as the x,
	//And the baseline of the text as the y
	Vector2f charPos{ text.findCharacterPos(charIndex) };

	//To adjust we can add the top of the text bounds
	charPos.y += text.getGlobalBounds().top;
	return charPos;
}

float Utils::GetCharacterWidth(const char& c, const unsigned int charSize, const Font& font, const bool bold)
{
	return font.getGlyph(static_cast<int>(c), charSize, bold).advance;
}

bool Utils::PosInBounds(const Vector2f pos, const Vector2f boundsPos, const Vector2f boundsSize)
{
	if (pos.x >= boundsPos.x && pos.x <= boundsPos.x + boundsSize.x) {
		if (pos.y >= boundsPos.y && pos.y <= boundsPos.y + boundsSize.y) {
			return true;
		}
	}

	return false;
}
