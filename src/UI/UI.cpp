//Work of Nicholas Egerton
#include "UI/UI.h"
#include "UI/SideBar.h"

using namespace sf;

UI::UI(Renderer& renderer) : renderer(renderer)
{
	//Setup childViewWidgets
	//ChildViewWidgets have their own , and are used for major widgets
	//That contains multiple child widgets, so that childWidgets are clipped
	//Within the ViewWidget's bounds. Note that child widgets use coordinates
	//Relative to the view of their ViewWidget.
	//UI however uses coordinates relative to the whole window
	Vector2f wSize{ renderer.GetSize() };
	childViewWidgets.push_back(std::make_unique<SideBar>(Vector2f(0, 0), Vector2f(wSize.x / 3, wSize.y), renderer.GetCambria(), Color(25, 25, 25), Vector2f(1.f / 3.f, 1)));
}

void UI::Draw()
{
	for (const auto& w : childViewWidgets) {
		renderer.SetView(w->GetView());
		renderer.Draw(*w);
	}
}

void UI::Update()
{
	for (const auto& w : childViewWidgets) {
		w->Update();
	}
}

EventResult UI::OnEvent(Event& event)
{
	EventResult consumedInput{ false, Cursor::Type::Arrow };
	for (const auto& w : childViewWidgets) {
		EventResult eventResult{ w->OnEvent(event) };
		if (eventResult.consumeInput) {
			consumedInput = eventResult;
		}
	}
	return consumedInput;
}
