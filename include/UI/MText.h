#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <stack>
#include <memory>
#include <string>
#include <vector>

class MText : public sf::Drawable, public sf::Transformable {
public:
	MText() = delete;
	MText(const sf::Vector2f pos, const sf::Vector2f size, const sf::Font& font, const std::wstring defaultText, const sf::Color fillColor);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Vector2f size;
	const sf::Font* font;
	std::wstring wString;
	sf::Color fillColor;

	void UpdateVertices();
	void UpdateKeywords();
	void AddGlyph(const sf::Glyph& glyph, const sf::Vector2f glyphPos, const unsigned int glyphSize, const sf::Color color);

	void ClearText();
	bool FormatGlyph(const wchar_t c, const sf::Vector2f glyphPos, const unsigned int glyphSize);

	void FormatPower(const bool start, const sf::Vector2f glyphPos, const unsigned int glyphSize);
	void FormatSquareRoot(const bool start, const sf::Vector2f glyphPos, const unsigned int glyphSize);

	struct SizedVertexArray {
		sf::VertexArray vertices;
		unsigned int size;
	};
	std::vector<SizedVertexArray> sizedVertexArrays;

	static const std::unordered_map<std::wstring, std::wstring> keywords;

	//Formatting:

	//The nest is made up of a stack of enums of the orders of types of formatting
	//E.g, for wString = "y = sqrt[[2^[[3]]]] + e^x
	//Nest would be = {sqrt, power, power}
	enum class Format {
		sqrt,
		power
	};
	std::stack<Format> nest;
	bool skipEscapeCharacter = false;

	//Transforms to apply, x: glyphPos.x, y: glyphPos.y, z: glyphSize
	//These are ADDED to these, not set, i.e "glyphPos.x += transformsToApply.x;"
	sf::Vector3f transformsToApply{ 0.f, 0.f, 0.f };

	std::vector<sf::RectangleShape> sqrtTops;
	std::stack<size_t> sqrtIndexes;
	float sqrtThicknessFactor{ 0.0525f };
public:
	const sf::Vector2f GetSize() const;
	void SetSize(const sf::Vector2f newSize);

	/// <summary>
	/// Get a pointer to the font used. 
	/// If there is no font, it returns a nullptr.
	/// </summary>
	const sf::Font* GetFont() const;
	/// <summary>
	/// <para>Set the font of the text. MText stores a pointer to the font, so if</para>
	/// the font is destroyed, this will cause undefined behaviour. This is the
	/// same as in sf::Text.
	/// </summary>
	void SetFont(const sf::Font& newPos);

	/// <summary>
	/// Get the wide string used by the text. 
	/// Wide strings are used to handle the extended unicode characters for math.
	/// </summary>
	const std::wstring& GetString() const;
	/// <summary>
	/// Set the wide string used by the text. 
	/// Wide strings are used to handle the extended unicode characters for math.
	/// </summary>
	void SetString(const std::wstring& newString);

	const sf::Color GetFillColor() const;
	void SetFillColor(const sf::Color color);

	/// <summary>
	/// <para>Get the thickness factor of the top of square roots in the text.</para>
	/// Different fonts have different shaped square roots, so this can be used
	/// to adjust. The default is 0.0525.
	/// </summary>
	const float GetSqrtThicknessFactor() const;
	/// <summary>
	/// <para>Set the thickness factor of the top of square roots in the text.</para>
	/// Different fonts have different shaped square roots, so this can be used
	/// to adjust.
	/// </summary>
	void SetSqrtThicknessFactor(const float newFactor);
};