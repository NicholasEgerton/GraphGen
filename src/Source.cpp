//Work of Nicholas Egerton
#include "SFML/Graphics.hpp"
#include "EventHandle.h"
#include "Renderer.h"
#include "UI.h"
#include <stdexcept>
#include "Errors.h"

using namespace sf;

int main()
{
    try {
        Renderer renderer;
        UI ui{ renderer };
        EventHandle eventHandle{ renderer, ui };

        while (renderer.GetWindow()->isOpen())
        {
            try {
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

            catch (const std::exception& e) {
                std::string msg{ "Runtime Error: " };
                msg += e.what();
                Errors::ShowError(msg);
                return EXIT_FAILURE;
            }
        }
    }

    catch (const std::exception& e) {
        std::string msg{ "Initialisation Error: " };
        msg += e.what();
        Errors::ShowError(msg);
        return EXIT_FAILURE;
    }

    catch (...) {
        Errors::ShowError("An unknown error occured.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}