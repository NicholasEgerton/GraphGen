//Work of Nicholas Egerton
#include "UI/SideBar.h"

using namespace sf;

SideBar::SideBar(const Vector2f pos, const Vector2f size, const Font& font, const Color backgroundCol) : Widget(pos, size), font(&font), backgroundCol(backgroundCol)
{
	background.setPosition(pos);
	background.setFillColor(backgroundCol);

	mText = std::make_unique<MText>(Utils::LocalToGlobalPos(sf::Vector2f(50.f, 100.f), pos), sf::Vector2f(size.x - 50.f, 60.f), font, L"y = e^[[x^[[2+pi]]-sqrt[[5x]]]] + sqrt[[3z^[[theta + 5^[[x]]]]]]", Color::White);
}

void SideBar::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(background, states);
	target.draw(*mText, states);
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
