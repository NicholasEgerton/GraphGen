#include "Axis.h"
#include "Utils.h"

Axis::Axis(Vector2i wSize, Font* Roboto)
{
    //Setup axis borders
    axisX = RectangleShape(Vector2f(wSize.x, 3));
    axisX.setPosition(Vector2f(0, wSize.x / 2));
    axisX.setFillColor(Color(255, 127, 80));
    axisY = RectangleShape(Vector2f(3, wSize.y));
    axisY.setPosition(Vector2f(wSize.x / 2, 0));
    axisY.setFillColor(Color(255, 127, 80));

    //Setup scale rects and texts
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

        horizontalScaleTexts.push_back(Text(Utils::FloatToString(xValue, 0), *Roboto, 20));
        horizontalScaleTexts[i].setPosition(Vector2f(hozPos.x - 20, hozPos.y + offset));
        horizontalScaleTexts[i].setFillColor(txtCol);

        horizontalScaleRects.push_back(RectangleShape(Vector2f(3, 10)));
        horizontalScaleRects[i].setPosition(Vector2f(hozPos.x, hozPos.y - 3));
        horizontalScaleRects[i].setFillColor(rectCol);

        verticalScaleTexts.push_back(Text(Utils::FloatToString(-yValue, 0), *Roboto, 20));
        verticalScaleTexts[i].setPosition(Vector2f(verPos.x + offset, verPos.y - 15));
        verticalScaleTexts[i].setFillColor(txtCol);

        verticalScaleRects.push_back(RectangleShape(Vector2f(10, 3)));
        verticalScaleRects[i].setPosition(Vector2f(verPos.x - 3, verPos.y));
        verticalScaleRects[i].setFillColor(rectCol);

        xValue += (wSize.x / 10);
        yValue += (wSize.x / 10);
    }
}
