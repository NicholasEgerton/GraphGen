//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"

class FunctionInputText : public Widget {
public:
	FunctionInputText() = delete;
	FunctionInputText(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, sf::Color backgroundCol, std::string defaultText,
		unsigned int charSize);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Update() override;
	virtual void OnClick(const sf::Event& event) override;
	virtual sf::Cursor::Type OnHover(const sf::Event& event) override;
	virtual void OnUnhover(const sf::Event& event) override;
	virtual void OnUnfocus(const sf::Event& event) override;

	virtual std::vector<Widget*> GetHoverableChildWidgets() override;
private:
	sf::Text text;
	sf::RectangleShape background = sf::RectangleShape(size);

	sf::RectangleShape caret;
	sf::Clock insertionClock;
};