//Work of Nicholas Egerton
#include "UI/SideBar.h"

using namespace sf;

SideBar::SideBar(const Vector2f pos, const Vector2f size, const Font& font, const Color backgroundCol, sf::Vector2f viewToWindowRatio) : ViewWidget(pos, size, viewToWindowRatio), font(&font), backgroundCol(backgroundCol),
mText(Vector2f(size.x * 0.0625f, size.y * 0.1f), Vector2f(size.x * 0.9375f, size.y * 0.075f), font, L"y = sqrt[[alpha^[[beta]] + theta^[[sqrt[[phi]]]]sqrt[[a]]sqrt[[c]]]]", Color::White)
{
	background.setPosition(Vector2f(0.f,0.f));
	background.setFillColor(backgroundCol);
}

void SideBar::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
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
	if (event.type == Event::Resized) {
		Vector2f newWSize{ static_cast<float>(event.size.width), static_cast<float>(event.size.height) };
		//Resize the view
		ResizeView(newWSize);
		//Always keep the sidebar the same ratio of the window
		background.setSize(Vector2f(newWSize.x * viewRatio.x, newWSize.y * viewRatio.y));
	}
	//Sidebar is not an InputWidget, so will mostly just call OnEvent()
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
