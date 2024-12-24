//Work of Nicholas Egerton
#include "SideBar.h"
#include "Utils.h"
#include "FunctionInputText.h"

using namespace sf;

SideBar::SideBar(Vector2f pos, Vector2f size, Font& font, Color backgroundCol) : Widget(pos, size), font(font), backgroundCol(backgroundCol)
{
	background.setPosition(pos);
	background.setFillColor(backgroundCol);

	childWidgets.push_back(std::make_unique<FunctionInputText>(Utils::LocalToGlobalPos(Vector2f(40, 10), pos),
		Vector2f(600, 60), font, Color(35, 35, 35), "y = x Êg", 40));
}

void SideBar::draw(RenderTarget& target, RenderStates states) const
{
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
