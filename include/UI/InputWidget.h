#pragma once

#include "SFML/Graphics.hpp"
#include "UI/Widget.h"
#include "UI/WidgetState.h"
#include "core/EventResult.h"

class InputWidget : public Widget {
public:
	InputWidget() = delete;
	InputWidget(sf::Vector2f pos, sf::Vector2f size) : Widget(pos, size) {};

	virtual EventResult OnEvent(const sf::Event& event);
protected:
	virtual EventResult OnClick(const sf::Event& event) { return { false, sf::Cursor::Arrow }; };
	virtual EventResult OnUnfocus(const sf::Event& event) { return { false, sf::Cursor::Arrow }; };
	virtual EventResult OnHover(const sf::Event& event) { return { false, sf::Cursor::Arrow }; };
	virtual EventResult OnUnhover(const sf::Event& event) { return { false, sf::Cursor::Arrow }; };
	virtual EventResult OnTextEntered(const sf::Event& event) { return { false, sf::Cursor::Arrow }; };

	WidgetState state = { false, false };

public:
	const WidgetState& GetState() const {
		return state;
	}
};