//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"
#include "EventResult.h"

class SideBar : public Widget {
public:
	SideBar() = delete;
	SideBar(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, sf::Color backgroundCol);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Update() override;
	virtual EventResult OnEvent(const sf::Event& event) override;
private:
	sf::Font& font;
	sf::Color backgroundCol;

	sf::RectangleShape background{ size };
	std::vector<std::unique_ptr<Widget>> childWidgets;
};