//Graph Gen
//Source
//Work of Nicholas Egerton

#include "SFML/Graphics.hpp"
#include "Parameters.h"
#include <iostream>
#include <iomanip>
#include "Utils.h"
#include "ZoomHandle.h"
#include "Axis.h"
#include "Input.h"

using namespace sf;

int main()
{

    //Create window and event
    RenderWindow window(VideoMode(1000, 1000), "GraphGen", Style::Titlebar | Style::Close);
    
    Event event; 

    //Load Sprites
    Texture iBeamTexture;
    if (!iBeamTexture.loadFromFile("idc_ibeam_white.png")) 
    {
        printf("Failed to load texture: idc_ibeam");
    }
    Sprite iBeam(iBeamTexture);
    iBeam.setColor(Color(255, 255, 255, 255));

    //Load fonts
    //Load Font "Roboto"

    Font Roboto;
    if (!Roboto.loadFromFile("Roboto.ttf")) {
        printf("Failed to load font: Roboto");
    }

    //Set up parameter window
    Parameters parameters(&window, &iBeam, &Roboto);

    //Generate default starting graph (y = x)
    parameters.Generate(Vector2i(window.getSize()), false);

    Axis axis = Axis(Vector2i(window.getSize()), &Roboto);

    Input input = Input(parameters, axis, window);
    
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            input.HandleEvents(event);
        }

        input.Update();

        //Update Parameter window
        parameters.Update();

        //Clear window
        window.clear(Color::Black);
        
        //Draw borders
        window.draw(axis.GetAxisX());
        window.draw(axis.GetAxisY());


        for (int i = 0; i < 8; i++) {
            window.draw(axis.GetHorizontalScaleTexts()[i]);
            window.draw(axis.GetVerticalScaleTexts()[i]);

            window.draw(axis.GetHorizontalScaleRects()[i]);
            window.draw(axis.GetVerticalScaleRects()[i]);
        }

        //Draw lines
        for (int i = 0; i < parameters.GetLinesVector().size(); i++) {
            window.draw(parameters.GetLinesVector()[i]);
        }

        window.display();
    }

    return 0;
}