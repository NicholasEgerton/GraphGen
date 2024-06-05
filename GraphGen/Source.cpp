//Graph Gen
//Source
//Work of Nicholas Egerton

#include "SFML/Graphics.hpp"
#include "Parameters.h"
#include <iostream>
#include <iomanip>
#include "Utils.h"

using namespace sf;

void ZoomScaleTexts(float delta, int precision, Text* horizontalScaleTexts, Text* verticalScaleTexts, RenderWindow* window) {

    float factor = 0;
    if (delta >= 1) {
        factor = 0.5;
    }

    else {
        factor = 2;
    }

    for (int i = 0; i < 8; i++) {
        std::string s = horizontalScaleTexts[i].getString();

        float f = std::stof(s);

        f *= factor;

        s = Utils::FloatToString(f, precision);

        horizontalScaleTexts[i].setString(s);

        f *= -1;
        s = Utils::FloatToString(f, precision);
        verticalScaleTexts[i].setString(s);
    }
}

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
                if (parameters.GetScale() >= 1) {
                    precision = 0;
                }

                std::cout << parameters.GetScale() << std::endl;
                //MIN LOWER BOUND OF 1.90735e-06
                if (parameters.GetScale() > 1.90735e-06) {
                    if (event.mouseWheelScroll.delta >= 1) {
                        parameters.SetScale(parameters.GetScale() / 2);
                        precision += 0.34f;
                        
                        ZoomScaleTexts(event.mouseWheelScroll.delta, static_cast<int>(roundf(precision)), horizontalScaleTexts, verticalScaleTexts, &window);
                        //The final argument true says to ignore the values
                        //Being the same as we are zooming
                        parameters.Generate(Vector2i(window.getSize()), true);
                    }
                }

                //MAX UPPPER BOUND OF 131072
                if (parameters.GetScale() < 131072) {
                    if (event.mouseWheelScroll.delta <= -1) {
                        parameters.SetScale(parameters.GetScale() * 2);
                        precision -= 0.34f;
                        
                        ZoomScaleTexts(event.mouseWheelScroll.delta, static_cast<int>(roundf(precision)), horizontalScaleTexts, verticalScaleTexts, &window);

                        //The final argument true says to ignore the values
                        //Being the same as we are zooming
                        parameters.Generate(Vector2i(window.getSize()), true);
                    }
                }
            }
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