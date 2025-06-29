//Work of Nicholas Egerton
#include "core/EventHandle.h"
#include "core/EventResult.h"

using namespace sf;

void EventHandle::Update()
{
    while(const std::optional<Event> event = renderer.PollEvent()) {
        if (event->is<Event::Closed>()) {
            renderer.Close();
        }

        EventResult eventResult{ ui.OnEvent(event) };

        if (eventResult.consumeInput && eventResult.newCursorType != currentCursorType) {
            renderer.SetCursor(eventResult.newCursorType);
            currentCursorType = eventResult.newCursorType;
        }
    }
}
