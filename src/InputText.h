//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "InputWidget.h"
#include "EventResult.h"

class InputText : public InputWidget {
public:
	InputText() = delete;
	InputText(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, sf::Color backgroundCol, std::string defaultText,
		unsigned int charSize);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Update() override;
protected:
	virtual EventResult OnClick(const sf::Event& event) override;
	virtual EventResult OnHover(const sf::Event& event) override;
	virtual EventResult OnUnhover(const sf::Event& event) override;
	virtual EventResult OnUnfocus(const sf::Event& event) override;

	unsigned int charSize;

	void UpdateCaret(sf::Vector2f mousePos);
	float FindCaretDisplacement(size_t charIndex, sf::Vector2f mousePos);
	float FindCharacterMiddleX(size_t charIndex);
	void MoveCaret(size_t charIndex);

	sf::Text text;
	sf::RectangleShape background{ size };

	sf::RectangleShape caret;
	sf::Clock caretClock;

	bool showCaret = false;
};