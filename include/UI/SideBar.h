//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "UI/Widget.h"
#include "core/EventResult.h"
#include "UI/MText.h"
#include "core/Utils.h"

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
	MText mText{ Utils::LocalToGlobalPos(sf::Vector2f(50.f, 30.f), pos), sf::Vector2f(size.x - 50.f, 50.f), font, L"y = theta +- pi * phi"};
	std::vector<std::unique_ptr<Widget>> childWidgets;
};