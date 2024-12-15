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
        //General flow of the program:
        //Clear->Input->UI->Display

        //The display is cleared
        renderer.Clear();

        //Events and input are handled
        eventHandle.Update();

        //The UI is updated and then drawn to the screen
        ui.Update();

        //They are then displayed
        renderer.Display();
    }

    return 0;
}