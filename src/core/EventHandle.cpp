//Work of Nicholas Egerton
#include "core/EventHandle.h"
#include "core/EventResult.h"

using namespace sf;

void EventHandle::Update()
{
    Event event;

    while(renderer.GetWindow()->pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                renderer.Close();
                break;

            case Event::Resized:
                renderer.Resize(Vector2u(event.size.width, event.size.height));
                break;
        }

        EventResult eventResult{ ui.OnEvent(event) };

        if (eventResult.consumeInput && eventResult.newCursorType != currentCursorType) {
            renderer.SetCursor(eventResult.newCursorType);
            currentCursorType = eventResult.newCursorType;
        }
    }
}
