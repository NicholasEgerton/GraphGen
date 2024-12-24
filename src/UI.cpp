//Work of Nicholas Egerton
#include "UI.h"
#include "SideBar.h"

using namespace sf;

UI::UI(Renderer& renderer) : renderer(renderer)
{
	//Setup childWidgets
	childWidgets.push_back(std::make_unique<SideBar>(Vector2f(0, 0), Vector2f(640, 1080), *renderer.GetCambria(), Color(25, 25, 25)));
}

void UI::Update()
{
	for (const auto& w : childWidgets) {
		w->Update();
	}
	for (const auto& w : childWidgets) {
		renderer.Draw(*w);
	}
}

EventResult UI::OnEvent(Event& event)
{
	EventResult consumedInput{ false, Cursor::Type::Arrow };
	for (const auto& w : childWidgets) {
		EventResult eventResult{ w->OnEvent(event) };
		if (eventResult.consumeInput) {
			consumedInput = eventResult;
		}
	}
	return consumedInput;
}
