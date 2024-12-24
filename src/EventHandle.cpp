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
                Vector2u newSize{ event.size.width, event.size.height };
                renderer.Resize(newSize);
        }

        EventResult eventResult{ ui.OnEvent(event) };

        if (eventResult.consumeInput && eventResult.newCursorType != currentCursorType) {
            renderer.SetCursor(eventResult.newCursorType);
            currentCursorType = eventResult.newCursorType;
        }
    }
}
