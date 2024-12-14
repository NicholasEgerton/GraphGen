//Work of Nicholas Egerton
#include "SFML/Graphics.hpp"
#include "EventHandle.h"
#include "Renderer.h"
#include "UI.h"

using namespace sf;

int main()
{
    static const VideoMode defaultWindowSize = VideoMode(1000, 1000);
    Renderer renderer = Renderer(std::make_unique<RenderWindow>(defaultWindowSize, "GraphGen"));

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