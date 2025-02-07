#include "UI/MText.h"
#include <iostream>
#include <assert.h>

using namespace sf;

MText::MText(const Vector2f pos, const Vector2f size, const Font& font, const std::wstring defaultText, const Color fillColor) : size(size), font(&font), wString(defaultText), fillColor(fillColor)
{
    setPosition(pos);
    UpdateKeywords();
    UpdateVertices();
}

void MText::draw(RenderTarget& target, RenderStates states) const
{
    states.transform *= getTransform();
    if (wString.empty()) {
        return;
    }

    for (const auto& sT: sqrtTops) {
        target.draw(sT, states);
    }

    for (const auto& sVA : sizedVertexArrays) {
        //Make sure the sizedVertexArray is valid
        if (sVA.vertices.getVertexCount() <= 0 || sVA.size <= 0) {
            continue;
        }
        //Set the states texture to the font at that size
        //So that the characters are rendered correctly
        states.texture = &font->getTexture(sVA.size);
        target.draw(sVA.vertices, states);
    }
}

void MText::UpdateVertices()
{
    ClearText();

    //Set the first glyphPos to the top left corner of mText (local coordinates)
    Vector2f glyphPos{ Vector2f(0, size.y / 2.f) };
    unsigned int glyphSize{ static_cast<unsigned int>(round(size.y)) };

    for (const auto& c : wString) {
        //Apply any formatting transforms
        glyphPos.x += transformsToApply.x;
        glyphPos.y += transformsToApply.y;
        glyphSize += static_cast<unsigned int>(transformsToApply.z);
        //Reset the transforms
        transformsToApply = { 0.f, 0.f, 0.f };

        const Glyph& glyph{ font->getGlyph(static_cast<Uint32>(c), glyphSize, false) };
        //Clip of the end of text if it goes outside the bounds width
        if (glyphPos.x + glyph.advance > size.x) {
            //Finish off remaining sqrtTops, and clear the sqrtIndexes in doing so
            while (!sqrtIndexes.empty()) {
                FormatSquareRoot(false, Vector2f(size.x, glyphPos.y), glyphSize);
            }
            //Clear nest
            nest = {};
            break;
        }
        //Skip the glyph if FormatGlyph() returns false
        if (FormatGlyph(c, glyphPos, glyphSize)) {
            //Don't add the glyph if it is just whitespace
            if (c != ' ') {
                AddGlyph(glyph, glyphPos, glyphSize, fillColor);
            }
            //Position the next glyph in front of the last
            glyphPos.x += glyph.advance;
        }
    }
}

void MText::ClearText()
{
    //Clear vertices
    for (auto& sVA : sizedVertexArrays) {
        sVA.vertices.clear();
    }
    //Reset formatting variables:
    transformsToApply = { 0.f, 0.f, 0.f };
    sqrtTops.clear();
    
    assert(!skipEscapeCharacter && "skipEscapeCharacter should not be true");
    assert(nest.empty() && "nest should be empty");
    assert(sqrtIndexes.empty() && "sqrtIndexes should be empty");
}

void MText::UpdateKeywords()
{
    static const std::unordered_map<std::wstring, std::wstring> keywords = {
    {L"alpha", L"\u03B1"}, {L"beta", L"\u03B2"}, {L"theta", L"\u03B8"}, {L"phi", L"\u03C6"}, {L"pi", L"\u03C0"},
    { L"*", L"\u00D7" }, { L"sqrt", L"\u221A" }, { L"+-", L"\u00B1", },
    };
    for (const auto& keyword : keywords) {
        size_t found{ wString.find(keyword.first) };
        while (found != std::string::npos) {
            wString.replace(found, keyword.first.length(), keyword.second);
            found = wString.find(keyword.first, found + 1);
        }
    }
}

void MText::AddGlyph(const Glyph& glyph, const Vector2f glyphPos, const unsigned int glyphSize, const Color color)
{
    //This function is very similar to Text::addGlyphQuad(), just
    //Slightly simplified and adjusted to fit the needs of this class
    const Vector2f padding{ 1.f, 1.f };
    const FloatRect bounds{ glyph.bounds };
    const IntRect textureRect{ glyph.textureRect };

    const Vector2f p1{ bounds.getPosition() - padding };
    const Vector2f p2{ bounds.getPosition() + bounds.getSize() + padding };

    const auto uv1{ Vector2f(textureRect.getPosition()) - padding };
    const auto uv2{ Vector2f(textureRect.getPosition() + textureRect.getSize()) + padding };

    //Find the associated vertex array
    VertexArray* vertices{ nullptr };
    for (auto& sVA : sizedVertexArrays) {
        if (sVA.size == glyphSize) {
            vertices = &sVA.vertices;
        }
    }

    //If there is no vertex array for this size, add one
    if (!vertices) {
        sizedVertexArrays.push_back({ VertexArray(Triangles), glyphSize });
        vertices = &sizedVertexArrays.back().vertices;
    }
    vertices->append({ glyphPos + Vector2f(p1.x, p1.y), color, {uv1.x, uv1.y} });
    vertices->append({ glyphPos + Vector2f(p2.x, p1.y), color, {uv2.x, uv1.y} });
    vertices->append({ glyphPos + Vector2f(p1.x, p2.y), color, {uv1.x, uv2.y} });
    vertices->append({ glyphPos + Vector2f(p1.x, p2.y), color, {uv1.x, uv2.y} });
    vertices->append({ glyphPos + Vector2f(p2.x, p1.y), color, {uv2.x, uv1.y} });
    vertices->append({ glyphPos + Vector2f(p2.x, p2.y), color, {uv2.x, uv2.y} });
}

bool MText::FormatGlyph(const wchar_t c, const Vector2f glyphPos, const unsigned int glyphSize)
{
    //This can modify the glyphPos and glyphSize to format the text
    //This function returns a bool on whether or not to skip this glyph
    switch (c) {
        //Skip escape sequence character
        case '[':
            return false;
        case '^':
            //Add power to the nest
            nest.push(Format::power);
            //Format the following text to be a power
            FormatPower(true, glyphPos, glyphSize);
            return false;
        case L'\u221A':
            //Add square root to the nest
            nest.push(Format::sqrt);
            //Format the following text to be under square root
            FormatSquareRoot(true, glyphPos, glyphSize);
            return true;
        case ']':
            //If it is the second ] in ]] do nothing
            if (skipEscapeCharacter) {
                skipEscapeCharacter = false;
                return false;
            }

            else if (!nest.empty()) {
                //Format based on what the top of the nest just ended
                if (nest.top() == Format::power) {
                    FormatPower(false, glyphPos, glyphSize);
                }

                else if (nest.top() == Format::sqrt) {
                    FormatSquareRoot(false, glyphPos, glyphSize);
                }

                else {
                    std::cout << "Unknown formatting found in MText.\n";
                    return false;
                }
                //Pop the stack
                nest.pop();
                
                skipEscapeCharacter = true;
            }
            return false;
    }
    return true;
}

void MText::FormatPower(const bool start, const Vector2f glyphPos, const unsigned int glyphSize)
{
    const float fGlyphSize{ static_cast<float>(glyphSize) };
    if (start) {
        //Divide the size by 2
        transformsToApply.z = round((fGlyphSize / 2.f) - fGlyphSize);
        //Offset the glyph up by the new glyph size
        transformsToApply.y = transformsToApply.z;
    }
    else {
        //Offset the glyph back down by the new glyph size
        transformsToApply.y = fGlyphSize;
        //Multiply the size back up by 2
        transformsToApply.z = round((fGlyphSize * 2.f) - fGlyphSize);
    }
}

void MText::FormatSquareRoot(const bool start, const Vector2f glyphPos, const unsigned int glyphSize)
{
    const float fGlyphSize{ static_cast<float>(glyphSize) };
    if (start) {
        transformsToApply.z = round((fGlyphSize / 1.25f) - fGlyphSize);

        const Vector2f padding{ 1.f, 1.f };
        //Get the sqrt glyph
        const Glyph& glyph{ font->getGlyph(static_cast<Uint32>(L'\u221A'), glyphSize, false) };
        //Set the thickness of the top of sqrt
        const float thickness{ static_cast<float>(glyphSize) * sqrtThicknessFactor };

        //Make a sqrtTop without width, but with height and position
        RectangleShape r{ Vector2f(0.f, thickness) };
        //Set the position to the top right corner of the sqrt glyph
        r.setPosition(Vector2f(glyphPos.x + glyph.advance, glyphPos.y + glyph.bounds.top) + padding);
        //Set the color of the sqrtTop
        r.setFillColor(fillColor);
        //Push the sqrtTop and add its index to the stack
        sqrtTops.push_back(r);
        sqrtIndexes.push(sqrtTops.size() - 1);
    }

    else {
        transformsToApply.z = round((fGlyphSize * 1.25f) - fGlyphSize);

        assert(!sqrtIndexes.empty() && "sqrtIndexes should not be empty");
        assert(sqrtIndexes.top() < sqrtTops.size() && "sqrtIndexes.top() should be in range");

        //Get the index of the most nested sqrtTop by getting the top of sqrtIndexes stack
        RectangleShape& r{ sqrtTops[sqrtIndexes.top()]};
        //Change the width to the distance since the sqrt started
        r.setSize(Vector2f(abs(glyphPos.x - r.getPosition().x), r.getSize().y));
        //Pop the stack
        sqrtIndexes.pop();
    }
}

//GET AND SETS:

const sf::Vector2f MText::GetSize() const
{
    return size;
}

void MText::SetSize(const sf::Vector2f newSize)
{
    size = newSize;
    UpdateVertices();
}

const sf::Font* MText::GetFont() const
{
    return font;
}

void MText::SetFont(const sf::Font& newFont)
{
    font = &newFont;
    UpdateVertices();
}

const std::wstring& MText::GetString() const
{
    return wString;
}

void MText::SetString(const std::wstring& newString)
{
    wString = newString;
    UpdateKeywords();
    UpdateVertices();
}

const sf::Color MText::GetFillColor() const
{
    return fillColor;
}

void MText::SetFillColor(const sf::Color newColor)
{
    fillColor = newColor;
    UpdateVertices();
}

const float MText::GetSqrtThicknessFactor() const
{
    return sqrtThicknessFactor;
}

void MText::SetSqrtThicknessFactor(const float newFactor)
{
    sqrtThicknessFactor = newFactor;
    UpdateVertices();
}
