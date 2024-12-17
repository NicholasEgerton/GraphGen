//Work of Nicholas Egerton
#include "UI.h"
#include "SideBar.h"

using namespace sf;

UI::UI(Renderer& renderer, EventHandle& eventHandle) : renderer(renderer), eventHandle(eventHandle)
{
	//Setup childWidgets
	childWidgets.push_back(std::make_unique<SideBar>(Vector2f(0, 0), Vector2f(333, 1000), *renderer.GetCambria(), Color(25, 25, 25)));

	//Find focusableChildWidgets and add them to EventHandle
	std::vector<Widget*> totalFocusable;
	//Loop through child widgets
	for (const auto& w : childWidgets) {
		//Append this childWidget's focusableChildWidgets to the total
		std::vector<Widget*> cW = w->GetFocusableChildWidgets();
		if (!cW.empty()) {
			totalFocusable.insert(totalFocusable.begin(), cW.begin(), cW.end());
		}
	}

	eventHandle.AddFocusableWidgets(totalFocusable);
}

void UI::Update()
{
	for (const auto& w : childWidgets) {
		renderer.Draw(*w);
	}
}
