//Work of Nicholas Egerton
#include "Parameters.h"
#include <iostream>
#include <algorithm>
#include "Utils.h"
#include <stack>
#include <algorithm>

using namespace sf;

Parameters::Parameters(RenderWindow& mainWindow, Sprite& iBeam, Font& font) 
    : mainWindow(&mainWindow), iBeam(&iBeam), font(&font)
{
    //Create the window
    window.create(VideoMode(500, 500), "Parameters", Style::Titlebar | Style::Close);

    //Put default values in aNCValues
    for (int i = 0; i < aNCValues.size(); ++i) {
        aNCValues[i] = { 1, 1, 0 };
    }

//SETUP Objects

    //Texts
    titleText = Text("Parameters:", font, 70);
    titleText.setPosition(50, 0);
    titleText.setFillColor(Color(150, 0, 0));
    titleText.setStyle(Text::Bold | Text::Underlined);

    infoText = Text("Type or use the sliders to adjust parameters.", font, 20);
    infoText.setPosition(40, 80);
    infoText.setFillColor(Color(0, 150, 0));

    aText = Text("a", font, 60);
    aText.setPosition(10, 120);
    aText.setFillColor(Color::Black);
    aText.setStyle(Text::Bold);

    nText = Text("n", font, 60);
    nText.setPosition(10, 241.5);
    nText.setFillColor(Color::Black);
    nText.setStyle(Text::Bold);

    cText = Text("c", font, 60);
    cText.setPosition(10, 362.5);
    cText.setFillColor(Color::Black);
    cText.setStyle(Text::Bold);

    //Input texts
    aInputText = InputText(Vector2f(60, 137), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, iBeam, font, window);
    nInputText = InputText(Vector2f(60, 258.5), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, iBeam, font, window);
    cInputText = InputText(Vector2f(60, 380), Vector2f(200, 50), 40, "0", 9, Color::White, Color::Black, iBeam, font, window);

    functionInputText = FunctionInputText(Vector2f(20, 325), Vector2f(460, 100), 70, "a(x)", 39, Color::White, Color::Black, iBeam, font, window);

    //Sliders
    aSlider = Slider(Vector2f(265, 157), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-1000, 1000), true, aInputText, window);
    nSlider = Slider(Vector2f(265, 278.5), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-10, 10), true, nInputText, window);
    cSlider = Slider(Vector2f(265, 400), Vector2f(225, 12.5), Color::White, Color::Black, 0, Vector2f(-500, 500), true, cInputText, window);

    //Buttons
    aButton = Button(Vector2f(410, 110), Vector2f(80, 30), Color::Black, Color::White, 30, "Large", "Small", font, window);
    modeButton = Button(Vector2f(10, 450), Vector2f(450, 30), Color::Black, Color::White, 30, "Switch To Composite Functions", "Switch To Singular Functions", font, window);

    //Tabs
    tabs = Tabs(Vector2f(5, 5), Vector2f(57, 25), 8, Color(255, 140, 0), Color::White, 25, font, aInputText, nInputText, cInputText, aSlider, nSlider, cSlider, window);
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
        //And only when they must change
        if (mode != modeButton.GetState()) {
            mode = modeButton.GetState();

            if (!mode) {
                //Texts
                aText = Text("a", *font, 60);
                aText.setPosition(10, 120);
                aText.setFillColor(Color::Black);
                aText.setStyle(Text::Bold);

                nText = Text("n", *font, 60);
                nText.setPosition(10, 241.5);
                nText.setFillColor(Color::Black);
                nText.setStyle(Text::Bold);

                cText = Text("c", *font, 60);
                cText.setPosition(10, 362.5);
                cText.setFillColor(Color::Black);
                cText.setStyle(Text::Bold);

                //Input texts
                aInputText = InputText(Vector2f(60, 137), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, *iBeam, *font, window);
                nInputText = InputText(Vector2f(60, 258.5), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, *iBeam, *font, window);
                cInputText = InputText(Vector2f(60, 380), Vector2f(200, 50), 40, "0", 9, Color::White, Color::Black, *iBeam, *font, window);

                //Sliders
                aSlider = Slider(Vector2f(265, 157), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-1000, 1000), true, aInputText, window);
                nSlider = Slider(Vector2f(265, 278.5), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-10, 10), true, nInputText, window);
                cSlider = Slider(Vector2f(265, 400), Vector2f(225, 12.5), Color::White, Color::Black, 0, Vector2f(-500, 500), true, cInputText, window);

                //Buttons
                aButton = Button(Vector2f(410, 110), Vector2f(80, 30), Color::Black, Color::White, 30, "Large", "Small", *font, window);
            }

            else {
                //Texts
                aText = Text("a", *font, 60);
                aText.setPosition(10, 60);
                aText.setFillColor(Color::Black);
                aText.setStyle(Text::Bold);

                nText = Text("n", *font, 60);
                nText.setPosition(10, 140.5);
                nText.setFillColor(Color::Black);
                nText.setStyle(Text::Bold);

                cText = Text("c", *font, 60);
                cText.setPosition(10, 221);
                cText.setFillColor(Color::Black);
                cText.setStyle(Text::Bold);

                //Input texts
                aInputText = InputText(Vector2f(60, 77), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, *iBeam, *font, window);
                nInputText = InputText(Vector2f(60, 158.5), Vector2f(200, 50), 40, "1", 9, Color::White, Color::Black, *iBeam, *font, window);
                cInputText = InputText(Vector2f(60, 241), Vector2f(200, 50), 40, "0", 9, Color::White, Color::Black, *iBeam, *font, window);

                //Sliders
                aSlider = Slider(Vector2f(265, 97), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-1000, 1000), true, aInputText, window);
                nSlider = Slider(Vector2f(265, 178.5), Vector2f(225, 12.5), Color::White, Color::Black, 1, Vector2f(-10, 10), true, nInputText, window);
                cSlider = Slider(Vector2f(265, 261), Vector2f(225, 12.5), Color::White, Color::Black, 0, Vector2f(-500, 500), true, cInputText, window);

                //Buttons
                aButton = Button(Vector2f(410, 50), Vector2f(80, 30), Color::Black, Color::White, 30, "Large", "Small", *font, window);
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
        if (!aButton.GetState()) {
            aSlider.SetValueBounds(Vector2f(-1000, 1000));
            aSlider.SetRounded(true);
        }

        else {
            aSlider.SetValueBounds(Vector2f(-0.01f, 0.01f));
            aSlider.SetRounded(false);
        }
    }

    //Update graph every frame at 60 frames a second
    //1 / 60 is approximately = 0.0167 (4.dp)

    if (clock.getElapsedTime().asSeconds() >= 0.0167f) {
        Generate(Vector2i(mainWindow->getSize()), false);
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

void Parameters::Generate(Vector2i defaultWindowSize, bool ignoreSame)
{
    if (!mode) { //Singular functions
        //Convert input text strings to std strings and convert to float
        //Set a, n, and c to those.

        std::string aString = static_cast<std::string>(aInputText.GetText().getString());
        std::string nString = static_cast<std::string>(nInputText.GetText().getString());
        std::string cString = static_cast<std::string>(cInputText.GetText().getString());

        //Don't generate if strings are empty
        if (aString.empty() || nString.empty() || cString.empty()) {
            return;
        }

        //Don't generate if strings are not a valid number
        if (!Utils::IsStringNum(aString) || !Utils::IsStringNum(nString) || !Utils::IsStringNum(cString)) {
            return;
        }

        //Don't generate if values have not changed
        if (a == std::stof(aString) && n == std::stof(nString) && c == std::stof(cString)) {
            if (!ignoreSame) {
                return;
            }
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
        std::string infix = functionInputText.GetText().getString();

        bool sameValues = true;

        for (int i = 0; i < aNCValues.size(); ++i) {
            Tabs::Tab tab = tabs.GetTabs()[i];
            if (aNCValues[i].a != tab.a || aNCValues[i].n != tab.n || aNCValues[i].c != tab.c) {
                aNCValues[i] = { tab.a, tab.n, tab.c };
                sameValues = false;
            }
        }

        if (sameValues && infix == oldInfix) {
            oldInfix = infix;
            return;
        }

        oldInfix = infix;

        //Remove spaces
        infix.erase(std::remove_if(infix.begin(), infix.end(), isspace), infix.end());
        
        //Validate infix
        if (!ValidateInfix(infix)) {
            return;
        }

        postfixExpression = InfixToPostfix(infix);
        CalculateLines(Vector2f(defaultWindowSize));
    }
}

void Parameters::CalculateLines(Vector2f defaultWindowSize)
{
    //FORM LINES
    //NOTE: Using default screen size so if the screen size changes
    //It simply stretches/constricts screen size instead of
    //Physically changing the lines

    linesVector.clear();
    linesVector.push_back(VertexArray(LineStrip));

    float x = -(defaultWindowSize.x / 2) * scale;
    float y = 0;

    int p = 0;

    int linesVectorIndex = 0;

    float lastX = 0;

    //Loop through all pixels on the screen
    for (p = 0; p < defaultWindowSize.x; p++) {
        y = CalculateY(x);

        //Checking if y is a real value
        if (!isnan(y) && !isinf(y)) {
            //If the lastX was NOT directly before
            //And the current x is not the first
            //Then there is an asymptote so split the lines
            if (lastX != x - scale && x != -(defaultWindowSize.x / 2) * scale) {
                x+= scale;
                linesVector.push_back(VertexArray(LinesStrip));
                linesVectorIndex++;
            };

            lastX = x;

            linesVector[linesVectorIndex].append(Vertex(ConvertPos(defaultWindowSize, x, y)));
        }

        x += scale;
    }
}

bool Parameters::ValidateInfix(std::string& infix)
{
    const std::string validCharacters = "abcdefghx()/*+-";
    const std::string aToH = "abcdefgh";
    const std::string operators = "/*+-";

    //a(x) = 4 char, a(x)+b(x) = 9, a(x)+b(x)-c(x) = 14 ect.
    //If f is number of functions and c is number of chars,
    //Our expression must satisfy: c = 5f - 1
    //8 is max amount of functions in functionInputText
    for (int f = 0; f < 8; ++f) {
        if (infix.size() == (5 * f - 1)) {
            break;
        }

        else if (f == 7) {
            return false;
        }
    }

    for (int i = 0; i < infix.size(); ++i) {
        //If it is in (abcdefgh), check if it follows with (x)
        if (aToH.find(infix[i]) != std::string::npos) {
            if (i + 3 < infix.size()) {
                if (infix.substr(i + 1, 3) != "(x)") {
                    return false;
                }
            }

            else {
                return false;
            }
        }
        //Check no two operators follow each other
        else if (operators.find(infix[i]) != std::string::npos) {
            if (i + 1 < infix.size()) {
                if (operators.find(infix[i + 1]) != std::string::npos) {
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

float Parameters::CalculateY(float x)
{
    //Singular functions
    if (!mode) {
        return (a * pow(x, n)) + c;
    }

    //Composite
    else { 
        std::string aToH = "abcdefgh";

        //Create a temp version of post fix (eq means equation)
        std::vector<std::string> eq = postfixExpression;

        //Replace function names with their terms at this x
        for (int i = 0; i < eq.size(); ++i) {
            if (aToH.find(eq[i][0]) != std::string::npos) {
                int functionIndex = aToH.find(eq[i][0]);
                float term = (aNCValues[functionIndex].a * pow(x, aNCValues[functionIndex].n)) + aNCValues[functionIndex].c;
                eq[i] = std::to_string(term);
            }
        }

        std::stack<float> result;
        
        for (int i = 0; i < eq.size(); ++i) {
            if (eq[i] == "/" || eq[i] == "*" || eq[i] == "+" || eq[i] == "-") {
                if (result.size() >= 2) {
                    float term2 = result.top();
                    result.pop();
                    float term1 = result.top();

                    switch (eq[i][0]) {
                    case '/':
                        result.top() = term1 / term2;
                        break;

                    case '*':
                        result.top() = term1 * term2;
                        break;

                    case '+':
                        result.top() = term1 + term2;
                        break;

                    case '-':
                        result.top() = term1 - term2;
                        break;
                    }
                }
                else {
                    std::cout << "(Parameters) Error: Invalid postfix!";
                    return 0;
                }
            }

            else {
                result.push(std::stof(eq[i]));
            }
        }

        return result.top();
    }
}

std::vector<std::string> Parameters::InfixToPostfix(std::string& infix)
{
    //Note: Shouldn't need to check much as it should have been validated

    std::vector<std::string> output;
    std::stack<char> operators;
    
    int i = 0;
    std::string aToH = "abcdefgh";

    while(i < infix.size()) {
        //If part of function name, add to the output
        if(aToH.find(infix[i]) != std::string::npos) {
            std::string newString = "(x)";
            newString.insert(newString.begin(), infix[i]);
            output.push_back(newString);
            //And skip past the (x)
            i += 4;
        }

        //If an operator, move any higher priority operators from the stack
        //To the output vector (push_back then pop)
        else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
            while (!operators.empty() && GetOperatorPriority(operators.top()) >= GetOperatorPriority(infix[i])) {
                output.push_back(std::string(1, operators.top()));
                operators.pop();
            }
            //Then push the new operator to the top of the stack
            operators.push(infix[i]);

            i++;
        }
    }

    //Then add any remaining operators to the end of the output
    while (!operators.empty()) {
        output.push_back(std::string(1, operators.top()));
        operators.pop();
    }

    return output;
}

Vector2f Parameters::ConvertPos(Vector2f defaultWindowSize, float x, float y) {
    x = (defaultWindowSize.x / 2) + x / scale;
    y = (defaultWindowSize.y / 2) - y / scale;
    return Vector2f(x, y);
}
