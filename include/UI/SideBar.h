//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "UI/ViewWidget.h"
#include "core/EventResult.h"
#include <memory>
#include <vector>

class SideBar : public ViewWidget {
public:
	SideBar() = delete;
	SideBar(const sf::Vector2f pos, const sf::Vector2f size, const sf::Font& font, const sf::Color backgroundCol, sf::Vector2f viewToWindowRatio);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update() override;
	EventResult OnEvent(const std::optional<sf::Event>& event) override;
private:
	const sf::Font* font;
	sf::Color backgroundCol;

	sf::RectangleShape background{ size };
	std::vector<std::unique_ptr<Widget>> childWidgets;
};