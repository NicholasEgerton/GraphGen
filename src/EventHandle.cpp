//Work of Nicholas Egerton
#include "EventHandle.h"

using namespace sf;

void EventHandle::Update()
{
    RenderWindow* window = renderer.GetWindow();
    Event event;

    while(window->pollEvent(event)) {
        if (event.type == Event::Closed)
        {
            window->close();
        }

        if (event.type == Event::Closed)
        {
            window->close();
        }

        if (event.type == Event::Resized) {
            View* view = renderer.GetView();
            Vector2f newSize = Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            view->setSize(newSize);
            window->setView(*view);
        }
    }
}
