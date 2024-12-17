//Work of Nicholas Egerton
#include "EventHandle.h"
#include "Utils.h"

using namespace sf;

void EventHandle::Update()
{
    Event event;

    while(renderer.GetWindow()->pollEvent(event)) {
        if (event.type == Event::Closed)
        {
            renderer.Close();
        }

        if (event.type == Event::Resized) {
            Vector2f newSize = Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            renderer.Resize(newSize);
        }

        if (event.type == Event::MouseMoved) {
            CheckForFocus(event);
        }

        if (event.type == Event::MouseButtonPressed) {
            OnClick(event);
        }
    }
}

void EventHandle::CheckForFocus(Event& event)
{
    Vector2f mousePos = Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
    bool focusFound = false;

    for (auto& w : focusableWidgets) {
        if (Utils::PosInBounds(mousePos, w->pos, w->size)) {
            focus = w;
            focusFound = true;
            break;
        };
    }

    if (!focusFound) {
        focus = nullptr;
    }
}

void EventHandle::OnClick(Event& event)
{
    if (focus) {
        focus->OnClick(event);
    }
}
