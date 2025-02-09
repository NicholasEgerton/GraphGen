//Work of Nicholas Egerton
#include "SFML/Graphics.hpp"
#include "core/EventHandle.h"
#include "core/Renderer.h"
#include "UI/UI.h"
#include "core/Errors.h"
#include <stdexcept>

using namespace sf;

int main()
{
    try {
        Renderer renderer;
        UI ui{ renderer };
        EventHandle eventHandle{ renderer, ui };

        while (renderer.IsOpen())
        {
            try {
                //General flow of the program:
                //Clear->Input->UI->Display

                //Clear display
                renderer.Clear();

                //Handle inputs and events
                eventHandle.Update();

                //Update UI
                ui.Update();

                //Draw UI
                ui.Draw();

                //Show display
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