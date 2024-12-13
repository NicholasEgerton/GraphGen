//Work of Nicholas Egerton
#include "SFML/Graphics.hpp"
#include "EventHandle.h"
#include "Renderer.h"

using namespace sf;

int main()
{
    static const VideoMode defaultWindowSize = VideoMode(1000, 1000);
    Renderer renderer = Renderer(std::make_unique<RenderWindow>(defaultWindowSize, "GraphGen"));

    EventHandle eventHandle = EventHandle(renderer);

    while (renderer.GetWindow()->isOpen())
    {
        eventHandle.Update();

        renderer.Update();
    }

    return 0;
}