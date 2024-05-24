//Graph Gen
//Source
//Work of Nicholas Egerton

#include "SFML/Graphics.hpp"
#include "Parameters.h"

using namespace sf;

int main()
{

    //Create window and event
    RenderWindow window(VideoMode(1000, 1000), "GraphGen");
    
    Event event; 

    //Load Sprites
    Texture iBeamTexture;
    if (!iBeamTexture.loadFromFile("images/idc_ibeam_white.png")) 
    {
        printf("Failed to load texture: idc_ibeam");
    }
    Sprite iBeam(iBeamTexture);
    iBeam.setColor(Color(255, 255, 255, 255));

    //Load fonts
    //Load Font "Roboto"

    Font Roboto;
    if (!Roboto.loadFromFile("fonts/Roboto.ttf")) {
        printf("Failed to load font: Roboto");
    }

    //Set up parameter window
    Parameters parameters(&window, &iBeam, &Roboto);

    //Generate default starting graph (y = x)
    parameters.Generate(Vector2i(window.getSize()), false);

    //Set up X and Y borders
    const Vector2f wSize = Vector2f(window.getSize());

    RectangleShape borderX(Vector2f(wSize.x, 3));
    borderX.setPosition(Vector2f(0, wSize.x / 2));
    borderX.setFillColor(Color(255, 127, 80));
    RectangleShape borderY(Vector2f(3, wSize.y));
    borderY.setPosition(Vector2f(wSize.x / 2, 0));
    borderY.setFillColor(Color(255, 127, 80));
    
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            //Allow the window to be closed
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseWheelScrolled) {
                //MIN LOWER BOUND OF 4.76837e-07
                if (parameters.GetScale() > 4.76837e-07) {
                    if (event.mouseWheelScroll.delta >= 1) {
                        parameters.SetScale(parameters.GetScale() / 2);
                    }
                }

                //MAX HIGHER BOUND OF 524288
                if (parameters.GetScale() < 524288) {
                    if (event.mouseWheelScroll.delta <= -1) {
                        parameters.SetScale(parameters.GetScale() * 2);
                    }
                }

                //The final argument true says to ignore the values
                //Being the same as we are zooming
                parameters.Generate(Vector2i(window.getSize()), true);
            }
        }

        //Update Parameter window
        parameters.Update();

        //Clear window
        window.clear(Color::Black);
        
        //Draw borders
        window.draw(borderX);
        window.draw(borderY);

        //Draw lines
        for (int i = 0; i < parameters.GetLinesVector().size(); i++) {
            window.draw(parameters.GetLinesVector()[i]);
        }

        window.display();
    }

    return 0;
}