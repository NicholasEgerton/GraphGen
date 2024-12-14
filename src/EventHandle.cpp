//Work of Nicholas Egerton
#include "EventHandle.h"

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
    }
}
