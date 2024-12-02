//Work of Nicholas Egerton
#include "Renderer.h"

using namespace sf;

void Renderer::Update() {
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