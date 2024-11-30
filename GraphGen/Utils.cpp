//Work of Nicholas Egerton
#include "Utils.h"
#include <sstream>
#include <iomanip>

using namespace sf;

std::string Utils::FloatToString(float f, int precision)
{
	std::stringstream stream;

	stream << std::fixed << std::setprecision(precision) << f;

	std::string newStr = stream.str();

	return newStr;
}

bool Utils::InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize)
{
	//Keeping in mind that the position of a rectangle is defined by its top left corner,
	//And the size increases from the top left corner
	//Checking if the point is > than the position and less than the size of the rect + position
	//Gives if the point is in the rect
	if (pointPos.x >= boundPos.x && pointPos.y >= boundPos.y) {
		if (pointPos.x <= boundPos.x + boundSize.x && pointPos.y <= boundPos.y + boundSize.y) {
			return true;
		}
	}

	return false;
}

bool Utils::IsStringNum(std::string string) {
    for (int i = 0; i < string.length(); i++) {
        if (!isdigit(string[i])) {
            if (string[i] == '-') {
                if (i != 0 || string.length() <= 1) {
                    return false;
                }
            }

            else if (string[i] == '.') {
                if (string.find_first_of('.') != string.find_last_of('.') || string.length() <= 1 || i == 0) {
                    return false;
                }

                else if (string[i - 1] == '-') {
                    return false;
                }
            }

            else {
                return false;
            }
        }
    }

    return true;
}