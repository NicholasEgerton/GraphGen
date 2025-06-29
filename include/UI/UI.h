#pragma once

#include "SFML/Graphics.hpp"
#include "core/Renderer.h"
#include "UI/ViewWidget.h"
#include "core/EventResult.h"
#include <memory>
#include <vector>

//The UI class manages and draws all view widgets on the screen,
//And view widgets may hold their own child widgets that they manage and draw.

class UI {
public:
	UI() = delete;
	UI(Renderer& renderer);

	void Draw();
	void Update();
	EventResult OnEvent(const std::optional<sf::Event>& event);
private:
	Renderer& renderer;

	std::vector<std::unique_ptr<ViewWidget>> childViewWidgets;
};