//Work of Nicholas Egerton
#include "UI/SideBar.h"

using namespace sf;

SideBar::SideBar(Vector2f pos, Vector2f size, Font& font, Color backgroundCol) : Widget(pos, size), font(font), backgroundCol(backgroundCol)
{
	background.setPosition(pos);
	background.setFillColor(backgroundCol);
}

void SideBar::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(background, states);
	target.draw(mText, states);
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

EventResult SideBar::OnEvent(const Event& event)
{
	//Sidebar is not an InputWidget, so will just call OnEvent()
	//On child widgets
	EventResult consumedInput{ false, Cursor::Type::Arrow };
	for (const auto& w : childWidgets) {
		EventResult eventResult{ w->OnEvent(event) };
		if (eventResult.consumeInput) {
			consumedInput = eventResult;
		}
	}
	return consumedInput;
}
