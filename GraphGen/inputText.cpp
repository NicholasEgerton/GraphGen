#include "InputText.h"

void InputText::Init(Vector2f pos, Vector2f size, float textSize, String defaultText, int maxChar, Color textCol, Color backgroundCol, Sprite* iBeam, Font* font, RenderWindow* window)
{
    //Setup received variables
    InputText::window = window;
    InputText::iBeam = iBeam;
    InputText::maxChar = maxChar;

    //Initialise the rect and text
    rect = RectangleShape(size);
    rect.setPosition(pos);
    rect.setFillColor(backgroundCol);

    text = Text(defaultText, *font, textSize);
    text.setFont(*font);
    text.setPosition(pos);
    text.setFillColor(textCol);
}

void InputText::Update(Event event)
{
    //Check if mouse is in rect
    if (InBounds(Mouse::getPosition(*window), rect.getPosition(), rect.getSize())) {
        inRect = true;
        iBeam->setPosition(static_cast<sf::Vector2f>(Mouse::getPosition(*window)));
        window->setMouseCursorVisible(false);
    }

    //Use of inRect, stop other input texts enabling mouse when they aren't meant to
    else if (inRect) {
        inRect = false;
        clickedRect = false;
        window->setMouseCursorVisible(true);
    }

    //Check if clicked the text box
    //clickedRect to stop other input texts taking others' text input
    if (inRect && event.type == Event::MouseButtonPressed) {
        clickedRect = true;
    }

    //Handle text input
    if (event.type == sf::Event::TextEntered && clickedRect) {

        String s = text.getString();

        text.setString(ValidText(event, s));
    }
}

bool InputText::InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize)
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

String InputText::ValidText(Event event, String s)
{
    //Backspace
    if (event.text.unicode == 8) {
        if (s.getSize()) {
            s.erase(s.getSize() - 1, s.getSize());
        }
    }
    //Typing
    //Make sure its not a letter and only 0-9 or decimal --> .
    else if (event.text.unicode >= 45 && event.text.unicode <= 57 && event.text.unicode != 47) {
        if (s.getSize() < maxChar) {
            s += static_cast<char>(event.text.unicode);
        }
    }

    return s;
}

void InputText::Draw()
{
    window->draw(rect);
    window->draw(text);

    if (inRect) {
        window->draw(*iBeam);
    }
}
