#include "SFML/Graphics.hpp"
#include "UI/InputWidget.h"
#include "core/Utils.h"

using namespace sf;

EventResult InputWidget::OnEvent(const std::optional<sf::Event>& event)
{
    //InputWidget by default has no child widgets,
    //So does not need to call OnEvent() on any.
    //Here, setup basic default bindings for events
    EventResult eventResult{ false, Cursor::Type::Arrow };
    FloatRect bounds{ getPosition(), size};
    if (const auto* mouseButtonPressed = event->getIf<Event::MouseButtonPressed>()) {
        if (bounds.contains(Vector2f(mouseButtonPressed->position))) {
            eventResult = OnClick(event);
        }

        else if (state.focused) {
            eventResult = OnUnfocus(event);
        }
    }

    else if (const auto* mouseMoved = event->getIf<Event::MouseMoved>()) {
        if (bounds.contains(Vector2f(mouseMoved->position))) {
            eventResult = OnHover(event);
        }

        else if (state.focused) {
            eventResult = OnUnhover(event);
        }
    }

    else if (const auto* textEntered = event->getIf<Event::TextEntered>()) {
        if (state.focused) {
            eventResult = OnTextEntered(event);
        }
    }
    return eventResult;
}
