#pragma once

#include "SFML/Graphics.hpp"
#include "UI/Widget.h"
#include "UI/WidgetState.h"
#include "core/EventResult.h"

class InputWidget : public Widget {
public:
	InputWidget() = delete;
	InputWidget(const sf::Vector2f pos, const sf::Vector2f size) : Widget(pos, size) {};

	virtual EventResult OnEvent(const std::optional<sf::Event>& event);
protected:
	virtual EventResult OnClick(const std::optional<sf::Event>& event) { return { false, sf::Cursor::Type::Arrow }; };
	virtual EventResult OnUnfocus(const std::optional<sf::Event>& event) { return { false, sf::Cursor::Type::Arrow }; };
	virtual EventResult OnHover(const std::optional<sf::Event>& event) { return { false, sf::Cursor::Type::Arrow }; };
	virtual EventResult OnUnhover(const std::optional<sf::Event>& event) { return { false, sf::Cursor::Type::Arrow }; };
	virtual EventResult OnTextEntered(const std::optional<sf::Event>& event) { return { false, sf::Cursor::Type::Arrow }; };

	WidgetState state = { false, false };

public:
	const WidgetState& GetState() const {
		return state;
	}
};