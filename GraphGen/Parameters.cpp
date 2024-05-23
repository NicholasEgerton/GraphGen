#include "Parameters.h"
#include <iostream>
#include <algorithm>

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
    nText.setPosition(10, 241.5);
    nText.setFillColor(Color::Black);
    nText.setStyle(Text::Bold);

    cText = Text("c", *Roboto, 60);
    cText.setPosition(10, 362.5);
    cText.setFillColor(Color::Black);
    cText.setStyle(Text::Bold);

    //Input texts
    aInputText.Init(Vector2f(60, 137), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, iBeam, Roboto, &window);
    nInputText.Init(Vector2f(60, 258.5), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, iBeam, Roboto, &window);
    cInputText.Init(Vector2f(60, 380), Vector2f(200, 50), 40, "0", 9, Color::White, Color::Black, iBeam, Roboto, &window);

    functionInputText.Init(Vector2f(20, 325), Vector2f(460, 100), 70, "a(x)", 39, Color::White, Color::Black, iBeam, Roboto, &window);

    //Sliders
    aSlider.Init(Vector2f(265, 157), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-1000, 1000), true, &aInputText, &window);
    nSlider.Init(Vector2f(265, 278.5), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-10, 10), true, &nInputText, &window);
    cSlider.Init(Vector2f(265, 400), Vector2f(225, 12.5), Color::White, Color::Black, 0, Vector2f(-500, 500), true, &cInputText, &window);

    //Buttons
    aButton.Init(Vector2f(410, 110), Vector2f(80, 30), Color::Black, Color::White, 30, "Large", "Small", Roboto, &window);
    modeButton.Init(Vector2f(10, 450), Vector2f(450, 30), Color::Black, Color::White, 30, "Switch To Composite Functions", "Switch To Singular Functions", Roboto, &window);

    //Tabs
    tabs.Init(Vector2f(5, 5), Vector2f(57, 25), 8, Color(255, 140, 0), Color::White, 25, Roboto, &aInputText, &nInputText, &cInputText, &aSlider, &nSlider, &cSlider, &window);
}


void Parameters::Update() {
    while (window.pollEvent(event))
    {
        //Allow the window to be closed
        if(event.type == Event::Closed) {
            window.close();
            mainWindow->close();
        }

        modeButton.Update(event);
        
        //If the mode has changed, regenerate the required elements (The universal ones)
        //To the new mode
        //This way, we are not resetting the objects every frame,
        //And only when we need to
        if (mode != modeButton.state) {
            mode = modeButton.state;

            if (!mode) {
                //Texts
                aText = Text("a", *Roboto, 60);
                aText.setPosition(10, 120);
                aText.setFillColor(Color::Black);
                aText.setStyle(Text::Bold);

                nText = Text("n", *Roboto, 60);
                nText.setPosition(10, 241.5);
                nText.setFillColor(Color::Black);
                nText.setStyle(Text::Bold);

                cText = Text("c", *Roboto, 60);
                cText.setPosition(10, 362.5);
                cText.setFillColor(Color::Black);
                cText.setStyle(Text::Bold);

                //Input texts
                aInputText.Init(Vector2f(60, 137), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, iBeam, Roboto, &window);
                nInputText.Init(Vector2f(60, 258.5), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, iBeam, Roboto, &window);
                cInputText.Init(Vector2f(60, 380), Vector2f(200, 50), 40, "0", 9, Color::White, Color::Black, iBeam, Roboto, &window);

                //Sliders
                aSlider.Init(Vector2f(265, 157), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-1000, 1000), true, &aInputText, &window);
                nSlider.Init(Vector2f(265, 278.5), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-10, 10), true, &nInputText, &window);
                cSlider.Init(Vector2f(265, 400), Vector2f(225, 12.5), Color::White, Color::Black, 0, Vector2f(-500, 500), true, &cInputText, &window);

                //Buttons
                aButton.Init(Vector2f(410, 110), Vector2f(80, 30), Color::Black, Color::White, 30, "Large", "Small", Roboto, &window);
            }

            else {
                //Texts
                aText = Text("a", *Roboto, 60);
                aText.setPosition(10, 60);
                aText.setFillColor(Color::Black);
                aText.setStyle(Text::Bold);

                nText = Text("n", *Roboto, 60);
                nText.setPosition(10, 140.5);
                nText.setFillColor(Color::Black);
                nText.setStyle(Text::Bold);

                cText = Text("c", *Roboto, 60);
                cText.setPosition(10, 221);
                cText.setFillColor(Color::Black);
                cText.setStyle(Text::Bold);

                //Input texts
                aInputText.Init(Vector2f(60, 77), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, iBeam, Roboto, &window);
                nInputText.Init(Vector2f(60, 158.5), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, iBeam, Roboto, &window);
                cInputText.Init(Vector2f(60, 241), Vector2f(200, 50), 40, "0", 9, Color::White, Color::Black, iBeam, Roboto, &window);

                //Sliders
                aSlider.Init(Vector2f(265, 97), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-1000, 1000), true, &aInputText, &window);
                nSlider.Init(Vector2f(265, 178.5), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-10, 10), true, &nInputText, &window);
                cSlider.Init(Vector2f(265, 261), Vector2f(225, 12.5), Color::White, Color::Black, 0, Vector2f(-500, 500), true, &cInputText, &window);

                //Buttons
                aButton.Init(Vector2f(410, 50), Vector2f(80, 30), Color::Black, Color::White, 30, "Large", "Small", Roboto, &window);
            }
        }

        if (mode) {
            functionInputText.Update(event);
            tabs.Update(event);
        }

        //UNIVERSAL TO BOTH MODES
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
            aSlider.valueBounds = Vector2f(-0.01f, 0.01f);
            aSlider.rounded = false;
        }
    }

    //Update graph every frame at 60 frames a second
    //1 / 60 is approximately = 0.0167 (4.dp)

    if (clock.getElapsedTime().asSeconds() >= 0.0167) {
        Generate(Vector2i(mainWindow->getSize()));
        clock.restart();
    }

    window.clear(Color(137, 207, 240));

    //MODE SPECIFIC
    if (!mode) {
        window.draw(titleText);
        window.draw(infoText);
    }

    else {
        functionInputText.Draw();
        tabs.Draw();
    }

    //UNIVERSAL TO BOTH MODES
    //Draw Texts
    window.draw(aText);
    window.draw(nText);
    window.draw(cText);

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
    modeButton.Draw();

    window.display();
}

void Parameters::Generate(Vector2i defaultWindowSize)
{
    if (!mode) { //Singular functions
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

        aSlider.ChangeBeamPos();
        nSlider.ChangeBeamPos();
        cSlider.ChangeBeamPos();

        a = std::stof(aString);
        n = std::stof(nString);
        c = std::stof(cString);

        CalculateLines(Vector2f(defaultWindowSize));

    }

    else { //Composite functions

        indexes.clear();
        mathOperations.clear();

        std::string s = functionInputText.text.getString();

        const std::string aToH = "abcdefgh";

        size_t length = s.length();

        //Dont gen if string is empty or less than minimum required string
        if (length < 4) { //Min is e.g "a(x)" which is 4 characters
            return;
        }

        int mathIndex = 0;

        //Save the + - / * in mathOperations
        for (size_t i = 0; i < length; i++) {
            switch(s[i]) {
                case '/':
                    mathOperations.push_back(Vector2i(0, mathIndex));
                    mathIndex++;
                    break;
                case '*':
                    mathOperations.push_back(Vector2i(1, mathIndex));
                    mathIndex++;
                    break;
                case '+':
                    mathOperations.push_back(Vector2i(2, mathIndex));
                    mathIndex++;
                    break;
                case '-':
                    mathOperations.push_back(Vector2i(3, mathIndex));
                    mathIndex++;
                    break;
            }
        }

        //Then sort them for bidmas

        std::sort(mathOperations.begin(), mathOperations.end(), Vector2iComparator());

        //Then remove them
        s.erase(std::remove_if(s.begin(), s.end(), [](char c)
            {
                return c == '+' || c == '-' || c == '*'
                    || c == '/';
            }),
            s.end());

        //Update length afterwards
        length = s.size();

        if (length < 4) {
            return;
        }

        //Now, loop through the string, and split into functions, e.g a(x) or b(x)
        // 
        //Here, we check if s[0] is a letter in a to h and if it is followed
        //with "(x)"

        int i = 0;
        while (length >= 4) {
            if (aToH.find(s[i]) != std::string::npos && s.substr(i + 1, 3) == "(x)") {
                //If so, we add to the indexes vector as the index of the letter
                //in a to h, this way we know which tab/function it is from
                indexes.push_back(aToH.find(s[i]));
                length -= 4;
                i += 4;
            }

            else {
                break;
            }
        }

        //Final check to make sure all good
        if (length != 0 || mathOperations.size() != indexes.size() - 1) {
            return;
        }

        //Finally, don't gen if the same values
        bool sameValues = true;

        if (aNCValues.size() == indexes.size()) {
            for (size_t i = 0; i < aNCValues.size(); i++) {
                if (aNCValues[i] != Vector3f(tabs.tabs[indexes[i]].a, tabs.tabs[indexes[i]].n, tabs.tabs[indexes[i]].c)) {
                    sameValues = false;
                };
            }
        }

        else {
            sameValues = false;
        }

        if (sameValues) {
            return;
        }

        else {
            aNCValues.clear();
            for (size_t i = 0; i < indexes.size(); i++) {
                aNCValues.push_back(Vector3f(tabs.tabs[indexes[i]].a, tabs.tabs[indexes[i]].n, tabs.tabs[indexes[i]].c));
            }
        }


        //Now we know the a, n and c values for the used functions in  var aNCValues
        //And the + - / * between them and var mathOperations
        CalculateLines(Vector2f(defaultWindowSize));
    }
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

void Parameters::CalculateLines(Vector2f defaultWindowSize)
{
    //FORM LINES
    //NOTE: Using default screen size so if the screen size changes
    //It simply stretches/constricts screen size instead of
    //Physically changing the lines

    linesVector.clear();
    linesVector.push_back(VertexArray(LineStrip));

    float x = -(defaultWindowSize.x / 2);
    float y = 0;

    int p = 0;

    int linesVectorIndex = 0;

    float lastX = 0;

    //Loop through all pixels on the screen
    for (p = 0; p < defaultWindowSize.x; p++) {
        y = CalculateY(x);

        //Note if y == y is to check if y is a nan value
        //Nan for some reason returns always false
        if (y == y) {
            if (lastX != x - 1 && x != -(defaultWindowSize.x / 2)) {
                x++;
                linesVector.push_back(VertexArray(LinesStrip));
                linesVectorIndex++;
            };

            lastX = x;

            linesVector[linesVectorIndex].append(Vertex(ConvertPos(defaultWindowSize, x, y)));
        }

        x++;
    }
}

float Parameters::CalculateY(float x)
{
    //Singular functions
    if (!mode) {
        return (a * pow(x, n)) + c;
    }

    //Composite
    else { 
        std::vector<float> termVector;
        float currentTerm;

        //Populate termVector
        for (int i = 0; i < aNCValues.size(); i++) {
            termVector.push_back((aNCValues[i].x * pow(x, aNCValues[i].y)) + aNCValues[i].z);
        }

        if (mathOperations.size() < 1) {
            return termVector[0];
        }

        currentTerm = termVector[mathOperations[0].y];

        size_t size = mathOperations.size();
        
        //Loop through all the operations and calculate in bidmas
        //Process example: 5 + "4" / 2 * 6 = 5 + "2" * 6 = 5 + 12 = 17
        //The currentTerm in example is in quotation marks

        for (int i = 0; i < size; i++) {
            switch (mathOperations[i].x) {
            case 0: //divide
                currentTerm /= termVector[mathOperations[i].y + 1];
                break;
            case 1: //multipy
                currentTerm *= termVector[mathOperations[i].y + 1];
                break;
            case 2: //add
                currentTerm += termVector[mathOperations[i].y + 1];
                break;
            case 3: //subtract
                currentTerm -= termVector[mathOperations[i].y + 1];
                break;
            }
        }
        return currentTerm;
    }
}

Vector2f Parameters::ConvertPos(Vector2f defaultWindowSize, float x, float y) {
    x = (defaultWindowSize.x / 2) + x;
    y = (defaultWindowSize.y / 2) - y;
    return Vector2f(x, y);
}