//Work of Nicholas Egerton
#include "Input.h"

using namespace sf;

void Input::HandleEvents(Event& event)
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
        ZoomHandle::Zoom(precision, event.mouseWheelScroll.delta, &parameters, axis.GetHorizontalScaleTexts(), axis.GetVerticalScaleTexts(), &window);
    }
}

void Input::Update()
{
    //Key zoom at approximately 30fps
    if (keyZoom.zooming && zoomClock.getElapsedTime().asSeconds() >= 0.033f) {
        ZoomHandle::Zoom(precision, keyZoom.key, &parameters, axis.GetHorizontalScaleTexts(), axis.GetVerticalScaleTexts(), &window);
        zoomClock.restart();
    }
}
