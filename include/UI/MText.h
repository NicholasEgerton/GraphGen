#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <stack>

//"MText" means "(Math)Text" and is a custom sf::Text class designed
//To handle formatting math. It has significantly less features than sf::Text,
//But is used where sf::Text cannot.
//[[ and ]] should be used in input as escape sequences, e.g:
//y = e^[[2x+1]] or y = sqrt[[x]] to avoid ambiguity
class MText : public sf::Drawable {
public:
	MText() = delete;
	MText(sf::Vector2f pos, sf::Vector2f size, const sf::Font& font, std::wstring defaultText);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f pos;
	sf::Vector2f size;
private:
	const sf::Font& font;
	std::wstring wString;

	void UpdateVertices();
	void UpdateKeywords();
	void AddGlyph(const sf::Vector2f glyphPos, const unsigned int glyphSize, const sf::Glyph& glyph, const sf::Color& color);

	bool FormatGlyph(const wchar_t c, sf::Vector2f& glyphPos, unsigned int& glyphSize);
	struct SizedVertexArray {
		sf::VertexArray vertices;
		unsigned int size;
	};

	std::vector<SizedVertexArray> sizedVertexArrays;

	const std::unordered_map<std::wstring, std::wstring> keywords{
		{L"theta", L"\u03B8"}, {L"+-", L"\u00B1",}, {L"pi", L"\u03C0"}, {L"phi", L"\u03C6"},
		{L"*", L"\u00D7"}
	};

	bool skipEscapeCharacter = false;
	unsigned int power;
	//The nest is made up of a stack of pointers to the type of function/special character
	//In order of how they were added
	//E.g for y = sqrt[[x^2]]
	//The nest would look like:
	//{[sqrt adress], [power adress]}
	std::stack<unsigned int*> nest;
};