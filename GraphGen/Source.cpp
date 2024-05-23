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
    Parameters parameters;
    parameters.Init(&window, &iBeam, &Roboto);

    //Generate default starting graph (y = x)
    parameters.Generate(Vector2i(window.getSize()));

    //Set up X and Y borders
    RectangleShape borderX(Vector2f(window.getSize().x, 3));
    borderX.setPosition(Vector2f(0, window.getSize().x / 2));
    borderX.setFillColor(Color(255, 127, 80));
    RectangleShape borderY(Vector2f(3, window.getSize().y));
    borderY.setPosition(Vector2f(window.getSize().x / 2, 0));
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
        }

        //Update Parameter window
        parameters.Update();

        //Clear window
        window.clear(Color::Black);
        
        //Draw borders
        window.draw(borderX);
        window.draw(borderY);

        //Draw lines
        for (int i = 0; i < parameters.linesVector.size(); i++) {
            window.draw(parameters.linesVector[i]);
        }

        window.display();
    }

    return 0;
}