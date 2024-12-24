#include "SFML/Graphics.hpp"
#include "InputWidget.h"
#include "Utils.h"

using namespace sf;

EventResult InputWidget::OnEvent(const Event& event)
{
    //InputWidget by default has no child widgets,
    //So does not need to call OnEvent() on any.
    //Here, setup basic default bindings for events
    EventResult eventResult{ false, Cursor::Arrow };
    Vector2f mousePos;
    switch (event.type) {
        case Event::MouseButtonPressed:
            mousePos = Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

            if (Utils::PosInBounds(mousePos, pos, size)) {
                eventResult = OnClick(event);
            }

            else if (state.focused) {
                eventResult = OnUnfocus(event);
            }
            break;
        case Event::MouseMoved:
            mousePos = Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
            if (Utils::PosInBounds(mousePos, pos, size)) {
                if (!state.hovered) {
                    eventResult = OnHover(event);
                }
            }

            else if (state.hovered) {
                eventResult = OnUnhover(event);
            }
            break;
    }
    return eventResult;
}
