//Work of Nicholas Egerton
#include "EventHandle.h"
#include "Utils.h"
#include <iostream>

using namespace sf;

EventHandle::EventHandle(Renderer& renderer) : renderer(renderer)
{
    //Load cursors
    if (!arrowCursor.loadFromSystem(Cursor::Arrow)) {
        std::cout << "(EventHandle) Error: Failed loading arrowCursor\n";
    }
    if (!textCursor.loadFromSystem(Cursor::Text)) {
        std::cout << "(EventHandle) Error: Failed loading textCursor\n";
    }
    currentCursorType = Cursor::Arrow;
}

void EventHandle::Update()
{
    Event event;

    while(renderer.GetWindow()->pollEvent(event)) {
        if (event.type == Event::Closed)
        {
            renderer.Close();
        }

        if (event.type == Event::Resized) {
            Vector2f newSize = Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            renderer.Resize(newSize);
        }

        if (event.type == Event::MouseMoved) {
            CheckForHover(event);
        }

        if (event.type == Event::MouseButtonPressed) {
            OnClick(event);
        }
    }
}

void EventHandle::CheckForHover(Event& event)
{
    Vector2f mousePos = Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
    bool hoverFound = false;

    //Loop through hoverable widgets and check if mouse is on them
    for (auto& w : hoverableWidgets) {
        if (Utils::PosInBounds(mousePos, w->pos, w->size)) {
            //If so, set them to the hover
            if (hover && hover != w) {
                hover->OnUnhover(event);
            }
            hover = w;
            hoverFound = true;
            break;
        };
    }
    //If there is a new hover or an old one
    if (hover) {
        //If a hover was found
        if (hoverFound) {
            //OnHover returns a cursorType, as well as doing it's own handling
            //Of being hovered
            Cursor::Type newCursorType = hover->OnHover(event);
            if (newCursorType != currentCursorType) {
                currentCursorType = newCursorType;
                switch (newCursorType) {
                case Cursor::Arrow:
                    renderer.GetWindow()->setMouseCursor(arrowCursor);
                    break;
                case Cursor::Text:
                    renderer.GetWindow()->setMouseCursor(textCursor);
                    break;
                }
            }
        }
        //If there was no hover found but there is an old one
        else if (!hoverFound) {
            hover->OnUnhover(event);
            hover = nullptr;
            //Set the cursor to the default arrow cursor
            if (currentCursorType != Cursor::Arrow) {
                currentCursorType = Cursor::Arrow;
                renderer.GetWindow()->setMouseCursor(arrowCursor);
            }
        }
    }
}

void EventHandle::OnClick(Event& event)
{
    if (hover) {
        //If the clicked hover is not the focus, unfocus the old one
        if (focus && hover != focus) {
            focus->OnUnfocus(event);
        }
        hover->OnClick(event);
        focus = hover;
    }
    //If there was an old focus and no hovered widget was clicked,
    //unhover the old focus
    else if (focus) {
        focus->OnUnfocus(event);
    }
}
