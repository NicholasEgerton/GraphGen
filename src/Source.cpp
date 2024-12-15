//Work of Nicholas Egerton
#include "SFML/Graphics.hpp"
#include "EventHandle.h"
#include "Renderer.h"
#include "UI.h"

using namespace sf;

int main()
{
    Renderer renderer = Renderer();

    EventHandle eventHandle = EventHandle(renderer);

    UI ui = UI(renderer);

    while (renderer.GetWindow()->isOpen())
    {
        renderer.Clear();

        eventHandle.Update();

        ui.Update();

        renderer.Display();
    }

    return 0;
}