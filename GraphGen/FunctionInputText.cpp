//Work of Nicholas Egerton
#include "FunctionInputText.h"

using namespace sf;

FunctionInputText::FunctionInputText(Vector2f pos, Vector2f size, unsigned int textSize, String defaultText, int maxChar, Color textCol, Color backgroundCol, Sprite& iBeam, Font& font, RenderWindow& window)
    : InputText(pos, size, textSize, defaultText, maxChar, textCol, backgroundCol, iBeam, font, window)
{
    FunctionInputText::charSize = static_cast<float>(textSize);
}

String FunctionInputText::ValidText(Event event, String s)
{
    Uint32 unicode = event.text.unicode;

    //Backspace
    if (unicode == 8) {
        if (s.getSize()) {
            s.erase(s.getSize() - 1, s.getSize());
        }

        //If the char Size is greater than default, dont increase
        //If it is, only actually set it to the charSize if it is in bounds
        if (charSize <= 68) {
            charSize += 2;
            if (charSize >= 18) {
                text.setCharacterSize(static_cast<unsigned int>(roundf(charSize)));
            }
        }
    }
    //Typing
    //Test if it is any of the following:
    else if (s.getSize() < maxChar) {

        char newChar = static_cast<char>(unicode);

        //Letter from a to h (lowercase)

        if (unicode >= 97 && unicode <= 104) {
            s = AddText(s, newChar);
        }

        //Letter from A to H (uppercase)
        if (unicode >= 65 && unicode <= 90) {
            //Ignore uppercase
            newChar = static_cast<char>(std::tolower(newChar));
            s = AddText(s, newChar);
        }

        // ( or )
        else if (unicode >= 40 && unicode <= 41) {
            s = AddText(s, newChar);
        }
        
        //X
        else if (unicode == 120) {
            s = AddText(s, newChar);
        }

        //+ or *
        else if (unicode >= 42 && unicode <= 43) {
            s = AddText(s, newChar);
        }

        // - or /
        else if (unicode == 45 || unicode == 47) {
            s = AddText(s, newChar);
        }
    }

    return s;
}

String FunctionInputText::AddText(String s, char stringToAdd)
{
    s += stringToAdd;

    //Only adjust text size if within the character size bounds
    if (charSize >= 2) {
        charSize -= 2;
        if (charSize >= 24) {
            text.setCharacterSize(static_cast<unsigned int>(roundf(charSize)));
        }
    }

    return s;
}