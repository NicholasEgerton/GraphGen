#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <stack>
#include <memory>

//"MText" means "(Math)Text" and is a custom sf::Text class designed
//To handle formatting math. It has significantly less features than sf::Text,
//But is used where sf::Text cannot.
//[[ and ]] should be used in input as escape sequences, e.g:
//y = e^[[2x+1]] or y = sqrt[[x]] to avoid ambiguity
class MText : public sf::Drawable {
public:
	MText() = delete;
	MText(const sf::Vector2f pos, const sf::Vector2f size, const sf::Font& font, const std::wstring defaultText, const sf::Color fillColor);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Vector2f pos;
	sf::Vector2f size;
	const sf::Font* font;
	std::wstring wString;
	sf::Color fillColor;

	void UpdateVertices();
	void UpdateKeywords();
	void AddGlyph(const sf::Vector2f glyphPos, const unsigned int glyphSize, const sf::Glyph& glyph, const sf::Color& color);

	bool FormatGlyph(const wchar_t c, const sf::Glyph& glyph, sf::Vector2f& glyphPos, unsigned int& glyphSize);

	void FormatPower(const bool start, sf::Vector2f& glyphPos, unsigned int& glyphSize);
	void FormatSquareRoot(const sf::Glyph& glyph, sf::Vector2f glyphPos, unsigned int& glyphSize);
	struct SizedVertexArray {
		sf::VertexArray vertices;
		unsigned int size;
	};

	std::vector<SizedVertexArray> sizedVertexArrays;

	const std::unordered_map<std::wstring, std::wstring> keywords{
		{L"theta", L"\u03B8"}, {L"+-", L"\u00B1",}, {L"pi", L"\u03C0"}, {L"phi", L"\u03C6"},
		{L"*", L"\u00D7"}, {L"sqrt", L"\u221A"}
	};

	bool skipEscapeCharacter = false;
	unsigned int power;
	unsigned int squareRoot;
	//The nest is made up of a stack of pointers to the type of function/special character
	//In order of how they were added
	//E.g for y = sqrt[[x^2]]
	//The nest would look like:
	//{[sqrt adress], [power adress]}
	std::stack<unsigned int*> nest;

public:
	const sf::Vector2f& GetPosition() const {
		return pos;
	}

	void SetPosition(const sf::Vector2f newPos) {
		pos = newPos;
		UpdateVertices();
	}

	const sf::Vector2f& GetSize() const {
		return size;
	}

	void SetSize(const sf::Vector2f newSize) {
		size = newSize;
		UpdateVertices();
	}


	const sf::Font& GetFont() const {
		return *font;
	}

	void SetFont(const sf::Font& newFont) {
		font = &newFont;
		UpdateVertices();
	}

	const std::wstring& GetString() const {
		return wString;
	}

	void SetString(const std::wstring newString) {
		wString = newString;
		UpdateKeywords();
		UpdateVertices();
	}

	const sf::Color& GetFillColor() const {
		return fillColor;
	}

	void SetFillColor(const sf::Color newColor) {
		fillColor = newColor;
		UpdateVertices();
	}
};