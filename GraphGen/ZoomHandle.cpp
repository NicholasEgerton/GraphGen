#include "ZoomHandle.h"
#include "Parameters.h"
#include "Utils.h"

using namespace sf;

void ZoomHandle::Zoom(float& precision, float& delta, Parameters* parameters, std::vector<Text>& horizontalScaleTexts, std::vector<Text>& verticalScaleTexts, RenderWindow* window) {

    if (parameters->GetScale() >= 1) {
        precision = 0;
    }

    //MIN LOWER BOUND OF 1.90735e-06
    if (parameters->GetScale() > 1.90735e-06) {
        if (delta >= 1) {
            parameters->SetScale(parameters->GetScale() / 2);
            precision += 0.34f;

            ZoomScaleTexts(delta, static_cast<int>(roundf(precision)), horizontalScaleTexts, verticalScaleTexts, window);
            //The final argument true says to ignore the values
            //Being the same as we are zooming
            parameters->Generate(Vector2i(window->getSize()), true);
        }
    }

    //MAX UPPPER BOUND OF 131072
    if (parameters->GetScale() < 131072) {
        if (delta <= -1) {
            parameters->SetScale(parameters->GetScale() * 2);
            precision -= 0.34f;

            ZoomScaleTexts(delta, static_cast<int>(roundf(precision)), horizontalScaleTexts, verticalScaleTexts, window);

            //The final argument true says to ignore the values
            //Being the same as we are zooming
            parameters->Generate(Vector2i(window->getSize()), true);
        }
    }
}

void ZoomHandle::ZoomScaleTexts(float delta, int precision, std::vector<Text>& horizontalScaleTexts, std::vector<Text>& verticalScaleTexts, RenderWindow* window) {

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