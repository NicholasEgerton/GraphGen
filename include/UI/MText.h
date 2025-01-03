#pragma once

#include "SFML/Graphics.hpp"
#include "UI/Widget.h"
#include <unordered_map>

//"MText" means "(Math)Text" and is a custom sf::Text class designed
//To handle formatting math. It has significantly less features than sf::Text,
//But is used where sf::Text cannot.
class MText : public Widget {
public:
	MText() = delete;
	MText(sf::Vector2f pos, sf::Vector2f size, const sf::Font& font, std::wstring defaultText);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	const sf::Font& font;
	std::wstring wString;

	void UpdateVertices();
	void UpdateKeywords();
	void AddGlyph(sf::Vector2f position, const sf::Glyph& glyph, const sf::Color& color);

	sf::VertexArray vertices{sf::Triangles};

	const std::unordered_map<std::wstring, std::wstring> keywords{ {L"theta", L"θ"}};
};