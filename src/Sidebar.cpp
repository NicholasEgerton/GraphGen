//Work of Nicholas Egerton
#include "SideBar.h"
#include "Utils.h"

using namespace sf;

SideBar::SideBar(Vector2f pos, Vector2f size, Font& font, Color backgroundCol) : Widget(pos, size), font(font), backgroundCol(backgroundCol)
{
	background.setPosition(pos);
	background.setFillColor(backgroundCol);

	childWidgets.push_back(std::make_unique<FunctionInputText>(Utils::LocalToGlobalPos(Vector2f(20, 10), pos),
		Vector2f(300, 75), font, Color(35, 35, 35), "y = x Êg", 50));
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

std::vector<Widget*> SideBar::GetHoverableChildWidgets()
{
	//Sidebar is not a hoverable widget, so will not include itself.
	std::vector<Widget*> hoverableChildWidgets;

	//Loop through child widgets
	for (const auto& w : childWidgets) {
		//Append this childWidget's hoverableChildWidgets to the total
		std::vector<Widget*> cW = w->GetHoverableChildWidgets();
		if (!cW.empty()) {
			hoverableChildWidgets.insert(hoverableChildWidgets.begin(), cW.begin(), cW.end());
		}
	}
	
	return hoverableChildWidgets;
}
