//Work of Nicholas Egerton
#include "UI/SideBar.h"

using namespace sf;

SideBar::SideBar(const Vector2f pos, const Vector2f size, const Font& font, const Color backgroundCol, sf::Vector2f viewToWindowRatio) : ViewWidget(pos, size, viewToWindowRatio), font(&font), backgroundCol(backgroundCol)
{
	background.setPosition(Vector2f(0.f,0.f));
	background.setFillColor(backgroundCol);
}

void SideBar::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(background, states);
	for (const auto& w : childWidgets) {
		target.draw(*w, states);
	}
}

void SideBar::Update()
{
	for (const auto& w : childWidgets) {
		w->Update();
	}
}

EventResult SideBar::OnEvent(const std::optional<sf::Event>& event)
{
	if (const auto* resized = event->getIf<Event::Resized>()) {
		Vector2f newWSize = Vector2f(resized->size);
		//Resize the view
		ResizeView(newWSize);
		//Always keep the sidebar the same ratio of the window
		background.setSize(Vector2f(newWSize.x * viewRatio.x, newWSize.y * viewRatio.y));
	}
	EventResult consumedInput{ false, Cursor::Type::Arrow };
	for (const auto& w : childWidgets) {
		EventResult eventResult{ w->OnEvent(event) };
		if (eventResult.consumeInput) {
			consumedInput = eventResult;
		}
	}
	return consumedInput;
}
