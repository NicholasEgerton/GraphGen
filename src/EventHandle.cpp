//Work of Nicholas Egerton
#include "EventHandle.h"
#include "EventResult.h"

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
                Vector2f newSize = Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                renderer.Resize(newSize);
        }
        if (event.type == Event::MouseButtonPressed) {
            int debug = 3;
            debug += 3;
        }
        EventResult eventResult = ui.OnEvent(event);

        if (eventResult.consumeInput && eventResult.newCursorType != currentCursorType) {
            renderer.SetCursor(eventResult.newCursorType);
            currentCursorType = eventResult.newCursorType;
        }
    }
}
