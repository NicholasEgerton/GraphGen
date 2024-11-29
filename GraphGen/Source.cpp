//Graph Gen
//Source
//Work of Nicholas Egerton

#include "SFML/Graphics.hpp"
#include "Parameters.h"
#include <iostream>
#include <iomanip>
#include "Utils.h"
#include "ZoomHandle.h"

using namespace sf;

int main()
{

    //Create window and event
    RenderWindow window(VideoMode(1000, 1000), "GraphGen", Style::Titlebar | Style::Close);
    
    Event event; 

    Vector2u oldWindowSize(1000, 1000);

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

    //Set up X and Y borders
    //Temporary first window size
    const Vector2f wSize = Vector2f(window.getSize());

    RectangleShape borderX(Vector2f(wSize.x, 3));
    borderX.setPosition(Vector2f(0, wSize.x / 2));
    borderX.setFillColor(Color(255, 127, 80));
    RectangleShape borderY(Vector2f(3, wSize.y));
    borderY.setPosition(Vector2f(wSize.x / 2, 0));
    borderY.setFillColor(Color(255, 127, 80));

    //Setup scale texts and scale rects
    Text* horizontalScaleTexts = new Text[8];
    Text* verticalScaleTexts = new Text[8];
    RectangleShape* horizontalScaleRects = new RectangleShape[8];
    RectangleShape* verticalScaleRects = new RectangleShape[8];

    //This insures the text is not directly on the border
    const int offset = 10;

    const Color txtCol = Color(0, 128, 175);
    const Color rectCol = Color(50, 150, 50);

    float xValue = (wSize.x / 10) - (wSize.x / 2);
    float yValue = (wSize.y / 10) - (wSize.y / 2);
    
    //Loop through the scale texts and rects and set them up
    for (int i = 0; i < 8; i++) {
        //Skip the 0 value
        if (i == 4) {
            xValue += (wSize.x / 10);
            yValue += (wSize.x / 10);
        }

        //Set the positions
        Vector2f hozPos = Vector2f(Vector2f(xValue + (wSize.y / 2), wSize.y / 2.f));
        Vector2f verPos = Vector2f(Vector2f(wSize.x / 2, yValue + (wSize.y / 2.f)));

        horizontalScaleTexts[i] = Text(Utils::FloatToString(xValue, 0), Roboto, 20);
        horizontalScaleTexts[i].setPosition(Vector2f(hozPos.x - 20, hozPos.y + offset));
        horizontalScaleTexts[i].setFillColor(txtCol);

        horizontalScaleRects[i] = RectangleShape(Vector2f(3, 10));
        horizontalScaleRects[i].setPosition(Vector2f(hozPos.x, hozPos.y - 3));
        horizontalScaleRects[i].setFillColor(rectCol);

        verticalScaleTexts[i] = Text(Utils::FloatToString(-yValue, 0), Roboto, 20);
        verticalScaleTexts[i].setPosition(Vector2f(verPos.x + offset, verPos.y - 15));
        verticalScaleTexts[i].setFillColor(txtCol);

        verticalScaleRects[i] = RectangleShape(Vector2f(10, 3));
        verticalScaleRects[i].setPosition(Vector2f(verPos.x - 3, verPos.y));
        verticalScaleRects[i].setFillColor(rectCol);

        xValue += (wSize.x / 10);
        yValue += (wSize.x / 10);
    }


    //How many decimal points on the scale
    float precision = 0;

    struct KeyZoom {
        bool zooming;
        float key; //-1 = -, 1 = +
    };

    KeyZoom keyZoom = { false, 0 };

    Clock zoomClock = Clock();
    
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            //Allow the window to be closed
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.scancode == Keyboard::Scan::Equal || event.key.scancode == Keyboard::Scan::NumpadPlus) {
                    keyZoom.zooming = true;
                    keyZoom.key = 1;
                }

                else if (event.key.scancode == Keyboard::Scan::Hyphen || event.key.scancode == Keyboard::Scan::NumpadMinus) {
                    keyZoom.zooming = true;
                    keyZoom.key = -1;
                }
            }

            if (event.type == Event::KeyReleased) {
                if (event.key.scancode == Keyboard::Scan::Equal || event.key.scancode == Keyboard::Scan::NumpadPlus) {
                    keyZoom.zooming = false;
                }

                else if (event.key.scancode == Keyboard::Scan::Hyphen || event.key.scancode == Keyboard::Scan::NumpadMinus) {
                    keyZoom.zooming = false;
                }
            }

            if (event.type == Event::MouseWheelScrolled) {
                ZoomHandle::Zoom(precision, event.mouseWheelScroll.delta, &parameters, horizontalScaleTexts, verticalScaleTexts, &window);
            }
        }

        //Key zoom at approximately 30fps
        if (keyZoom.zooming && zoomClock.getElapsedTime().asSeconds() >= 0.033f) {
            ZoomHandle::Zoom(precision, keyZoom.key, &parameters, horizontalScaleTexts, verticalScaleTexts, &window);
            zoomClock.restart();
        }

        //Update Parameter window
        parameters.Update();

        //Clear window
        window.clear(Color::Black);
        
        //Draw borders
        window.draw(borderX);
        window.draw(borderY);


        for (int i = 0; i < 8; i++) {
            window.draw(horizontalScaleTexts[i]);
            window.draw(verticalScaleTexts[i]);

            window.draw(horizontalScaleRects[i]);
            window.draw(verticalScaleRects[i]);
        }

        //Draw lines
        for (int i = 0; i < parameters.GetLinesVector().size(); i++) {
            window.draw(parameters.GetLinesVector()[i]);
        }

        window.display();
    }

    delete[] horizontalScaleTexts;
    delete[] verticalScaleTexts;
    delete[] horizontalScaleRects;
    delete[] verticalScaleRects;

    return 0;
}