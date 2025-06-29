#include "UI/ViewWidget.h"

using namespace sf;

ViewWidget::ViewWidget(const sf::Vector2f pos, const sf::Vector2f size, const sf::Vector2f viewToWindowRatio) : Widget(pos, size), viewRatio(viewToWindowRatio)
{
	//Set the viewport to the ratio of the window
	view.setViewport(FloatRect(getPosition(), viewRatio));
}

void ViewWidget::ResizeView(Vector2f newWSize)
{
	//Resize the view to be the same ratio of the window
	Vector2f newVSize{ newWSize.x * viewRatio.x, newWSize.y * viewRatio.y };
	view.setSize(newVSize);
	view.setCenter(getPosition() + Vector2f(newVSize.x / 2, newVSize.y / 2));
}
