#include "Parameters.h"

using namespace sf;

void Parameters::Init(RenderWindow* mainWindow, Sprite* iBeam, Font* Roboto) {
    //Setup Received variables
    Parameters::mainWindow = mainWindow;
    Parameters::Roboto = Roboto;
    Parameters::iBeam = iBeam;

    //Create the window
    window.create(VideoMode(500, 500), "Parameters");

    //Init clock
    clock = Clock();

//SETUP Objects (I kinda hate the boilerplate needed but sigh it seems its required)

    //Texts
    titleText = Text("Parameters:", *Roboto, 70);
    titleText.setPosition(50, 0);
    titleText.setFillColor(Color(150, 0, 0));
    titleText.setStyle(Text::Bold | Text::Underlined);

    infoText = Text("Type or use the sliders to adjust parameters.", *Roboto, 20);
    infoText.setPosition(40, 80);
    infoText.setFillColor(Color(0, 150, 0));

    aText = Text("a", *Roboto, 60);
    aText.setPosition(10, 120);
    aText.setFillColor(Color::Black);
    aText.setStyle(Text::Bold);

    nText = Text("n", *Roboto, 60);
    nText.setPosition(10, 270);
    nText.setFillColor(Color::Black);
    nText.setStyle(Text::Bold);

    cText = Text("c", *Roboto, 60);
    cText.setPosition(10, 420);
    cText.setFillColor(Color::Black);
    cText.setStyle(Text::Bold);

    //Input texts
    aInputText.Init(Vector2f(60, 137.5), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, iBeam, Roboto, &window);
    nInputText.Init(Vector2f(60, 270), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, iBeam, Roboto, &window);
    cInputText.Init(Vector2f(60, 420), Vector2f(200, 50), 40, "0", 9, Color::White, Color::Black, iBeam, Roboto, &window);

    //Sliders
    aSlider.Init(Vector2f(265, 157.5), Vector2f(225, 12.5), Color::White, Color::Black, Vector2f(-1000, 1000), true, &aInputText, &window);
    nSlider.Init(Vector2f(265, 290), Vector2f(225, 12.5), Color::White, Color::Black, Vector2f(-10, 10), true, &nInputText, &window);
    cSlider.Init(Vector2f(265, 440), Vector2f(225, 12.5), Color::White, Color::Black, Vector2f(-500, 500), true, &cInputText, &window);

    //Buttons
    aButton.Init(Vector2f(410, 110), Vector2f(80, 30), Color::Black, Color::White, 30, "Large", "Small", Roboto, &window);
}


void Parameters::Update() {
    while (window.pollEvent(event))
    {
        //Allow the window to be closed
        if(event.type == Event::Closed) {
            window.close();
            mainWindow->close();
        }
        //Update Input Texts
        aInputText.Update(event);
        nInputText.Update(event);
        cInputText.Update(event);

        //Update Sliders
        aSlider.Update(event);
        nSlider.Update(event);
        cSlider.Update(event);

        //Update Buttons
        aButton.Update(event);

        //Change aSlider based on aButton
        if (!aButton.state) {
            aSlider.valueBounds = Vector2f(-1000, 1000);
            aSlider.rounded = true;
        }

        else {
            aSlider.valueBounds = Vector2f(-0.01, 0.01);
            aSlider.rounded = false;
        }
    }
    window.clear(Color(137, 207, 240));

    //Draw Texts
    window.draw(titleText);
    window.draw(infoText);
    window.draw(aText);
    window.draw(nText);
    window.draw(cText);

    //Update graph every frame at 60 frames a second
    //1 / 60 is approximately = 0.0167 (4.dp) 

    if (clock.getElapsedTime().asSeconds() >= 0.0167) {
        Generate(Vector2i(mainWindow->getSize()));
        clock.restart();
    }

    //Draw Input Texts
    aInputText.Draw();
    nInputText.Draw();
    cInputText.Draw();

    //Draw Sliders
    aSlider.Draw();
    nSlider.Draw();
    cSlider.Draw();

    //Draw Buttons
    aButton.Draw();

    window.display();
}

void Parameters::Generate(Vector2i defaultWindowSize)
{
    //Convert input text strings to std strings and convert to float
    //Set a, n, and c to those.

    std::string aString = static_cast<std::string>(aInputText.text.getString());
    std::string nString = static_cast<std::string>(nInputText.text.getString());
    std::string cString = static_cast<std::string>(cInputText.text.getString());

    //Don't generate if strings are empty
    if (aString.empty() || nString.empty() || cString.empty()) {
        return;
    }

    //Don't generate if strings are not a valid number
    if (!IsNum(aString) || !IsNum(nString) || !IsNum(cString)) {
        return;
    }

    //Don't generate if values have not changed
    if (a == std::stof(aString) && n == std::stof(nString) && c == std::stof(cString)) {
        return;
    }

    a = std::stof(aString);
    n = std::stof(nString);
    c = std::stof(cString);

    printf("\n \n SPLIT \n \n");

    CalculateLines(defaultWindowSize);
}

bool Parameters::IsNum(std::string string) {
    for (int i = 0; i < string.length(); i++) {
        if (!isdigit(string[i])) {
            if (string[i] == '-') {
                if (i != 0 || string.length() <= 1) {
                    return false;
                }
            }

            else if (string[i] == '.') {
                if (string.find_first_of('.') != string.find_last_of('.') || string.length() <= 1) {
                    return false;
                }

                else if (string[i - 1] == '-') {
                    return false;
                }
            }

            else {
                return false;
            }
        }
    }

    return true;
}

void Parameters::CalculateLines(Vector2i defaultWindowSize)
{
    //FORM LINES
    //Initialise array with max value of default window width * 2
    //Note: using default screen size as to which if screen size is changed it 
    //Stretches instead of messing it up
    lines1 = { new Vertex[defaultWindowSize.x * 2] };

    float x = -(defaultWindowSize.x / 2);
    float y = 0;

    int index = 0;

    int p = 0;

    float lastX = 0;

    asymptote = false;

    //Loop through all pixels on the screen
    for (p = 0; p < defaultWindowSize.x; p++) {
        y = (a * pow(x, n)) + c;

        //Note if y == y is to check if y is a nan value
        //Nan for some reason returns always false
        if (y >= -(defaultWindowSize.y / 2) && y <= (defaultWindowSize.y / 2) && y == y) {

            if (lastX != x - 1 && index != 0) {
                asymptote = true;
                break;
            };
            lastX = x;

            
            lines1[index].position = ConvertPos(defaultWindowSize, x, y);

            if (index != 0 && index + 1 < (defaultWindowSize.x * 2)) {
                lines1[index + 1].position = ConvertPos(defaultWindowSize, x, y);
                index++;
            }

            index++;

            
        }

        x++;
    }

    line1Density = index;

    //ONLY If there is an asymptote, run again through the rest

    if (asymptote) {
        //Loop through the rest of the pixels
        lines2 = { new Vertex[defaultWindowSize.x * 2] };

        index = 0;

        for (p = p; p < defaultWindowSize.x; p++) {
            y = (a * pow(x, n)) + c;

            //Note if y == y is to check if y is a nan value
            //Nan for some reason returns always false
            if (y >= -(defaultWindowSize.y / 2) && y <= (defaultWindowSize.y / 2) && y == y) {

                lines2[index].position = ConvertPos(defaultWindowSize, x, y);

                if (index != 0 && index + 1 < (defaultWindowSize.x * 2)) {
                    lines2[index + 1].position = ConvertPos(defaultWindowSize, x, y);
                    index++;
                }

                index++;
            }

            x++;
        }
        line2Density = index;
    }


}

Vector2f Parameters::ConvertPos(Vector2i defaultWindowSize, int x, int y) {
    x = (defaultWindowSize.x / 2) + x;
    y = (defaultWindowSize.y / 2) - y;
    return Vector2f(x, y);
}
