//Work of Nicholas Egerton
#include "Axis.h"
#include "Utils.h"

using namespace sf;

Axis::Axis(Vector2f wSize, const Font& Roboto)
{
    //Setup axis borders
    axisX = RectangleShape(Vector2f(wSize.x, 3.f));
    axisX.setPosition(Vector2f(0.f, wSize.x / 2.f));
    axisX.setFillColor(Color(255, 127, 80));
    axisY = RectangleShape(Vector2f(3.f, wSize.y));
    axisY.setPosition(Vector2f(wSize.x / 2.f, 0.f));
    axisY.setFillColor(Color(255, 127, 80));

    //Setup scale rects and texts
    float xValue = (wSize.x / 10.f) - (wSize.x / 2.f);
    float yValue = (wSize.y / 10.f) - (wSize.y / 2.f);

    //Loop through the scale texts and rects and set them up
    for (int i = 0; i < 8; i++) {
        //Skip the 0 value
        if (i == 4) {
            xValue += (wSize.x / 10.f);
            yValue += (wSize.x / 10.f);
        }

        //Set the positions
        Vector2f hozPos = Vector2f(Vector2f(xValue + (wSize.y / 2.f), wSize.y / 2.f));
        Vector2f verPos = Vector2f(Vector2f(wSize.x / 2.f, yValue + (wSize.y / 2.f)));

        horizontalScaleTexts.push_back(Text(Utils::FloatToString(xValue, 0), Roboto, 20));
        horizontalScaleTexts[i].setPosition(Vector2f(hozPos.x - 20.f, hozPos.y + offset));
        horizontalScaleTexts[i].setFillColor(txtCol);

        horizontalScaleRects.push_back(RectangleShape(Vector2f(3.f, 10.f)));
        horizontalScaleRects[i].setPosition(Vector2f(hozPos.x, hozPos.y - 3));
        horizontalScaleRects[i].setFillColor(rectCol);

        verticalScaleTexts.push_back(Text(Utils::FloatToString(-yValue, 0), Roboto, 20));
        verticalScaleTexts[i].setPosition(Vector2f(verPos.x + offset, verPos.y - 15.f));
        verticalScaleTexts[i].setFillColor(txtCol);

        verticalScaleRects.push_back(RectangleShape(Vector2f(10.f, 3.f)));
        verticalScaleRects[i].setPosition(Vector2f(verPos.x - 3.f, verPos.y));
        verticalScaleRects[i].setFillColor(rectCol);

        xValue += (wSize.x / 10.f);
        yValue += (wSize.x / 10.f);
    }
}
