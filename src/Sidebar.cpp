//Work of Nicholas Egerton
#include "SideBar.h"
#include "Utils.h"

using namespace sf;

SideBar::SideBar(sf::Vector2f pos, sf::Vector2f size, Font& font, sf::Color backgroundCol) : Widget(pos, size), font(font), backgroundCol(backgroundCol)
{
	background.setPosition(pos);
	background.setFillColor(backgroundCol);

	childWidgets.push_back(std::make_unique<FunctionInputText>(Utils::LocalToGlobalPos(sf::Vector2f(20, 10), pos),
		sf::Vector2f(300, 75), font, Color(35, 35, 35), "y = x", 50));
}

void SideBar::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(background, states);
	for (const auto& w : childWidgets) {
		target.draw(*w, states);
	}
}

std::vector<Widget*> SideBar::GetFocusableChildWidgets()
{
	//Sidebar is not a focusable widget, so will not include itself.
	std::vector<Widget*> focusableChildWidgets;

	//Loop through child widgets
	for (const auto& w : childWidgets) {
		//Append this childWidget's focusableChildWidgets to the total
		std::vector<Widget*> cW = w->GetFocusableChildWidgets();
		if (!cW.empty()) {
			focusableChildWidgets.insert(focusableChildWidgets.begin(), cW.begin(), cW.end());
		}
	}
	
	return focusableChildWidgets;
}
