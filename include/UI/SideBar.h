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
	SideBar(const sf::Vector2f pos, const sf::Vector2f size, const sf::Font& font, const sf::Color backgroundCol);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Update() override;
	virtual EventResult OnEvent(const sf::Event& event) override;
private:
	const sf::Font* font;
	sf::Color backgroundCol;

	sf::RectangleShape background{ size };
	std::unique_ptr<MText> mText;
	std::vector<std::unique_ptr<Widget>> childWidgets;
};