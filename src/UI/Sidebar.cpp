//Work of Nicholas Egerton
#include "UI/SideBar.h"

using namespace sf;

SideBar::SideBar(const Vector2f pos, const Vector2f size, const Font& font, const Color backgroundCol) : Widget(pos, size), font(&font), backgroundCol(backgroundCol)
{
	background.setPosition(Vector2f(0.f,0.f));
	background.setFillColor(backgroundCol);

	mText = std::make_unique<MText>(Vector2f(50.f, 100.f), sf::Vector2f(size.x - 50.f, 55.f), font, L"y = sqrt[[alpha^[[beta]] + theta^[[sqrt[[phi]]]]sqrt[[a]]sqrt[[c]]]]", Color::White);
	mText->SetSize(Vector2f(size.x - 50.f, 100.f));
}

void SideBar::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
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
