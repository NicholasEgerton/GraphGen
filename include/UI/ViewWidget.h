#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"

class ViewWidget : public Widget {
public:
	ViewWidget() = delete;
	ViewWidget(const sf::Vector2f pos, const sf::Vector2f size, const sf::Vector2f viewToWindowRatio);

	void ResizeView(sf::Vector2f newWSize);
protected:
	sf::Vector2f viewRatio;

	sf::View view{ sf::FloatRect(getPosition(), size)};

public:
	const sf::View& GetView() const {
		return view;
	}
};