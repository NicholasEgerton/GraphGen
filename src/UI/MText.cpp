#include "UI/MText.h"
#include <iostream>

using namespace sf;

MText::MText(const Vector2f pos, const Vector2f size, const Font& font, const std::wstring defaultText, const Color fillColor) : pos(pos), size(size), font(&font), wString(defaultText), fillColor(fillColor)
{
    UpdateKeywords();
    UpdateVertices();
}

void MText::draw(RenderTarget& target, RenderStates states) const
{
    if (wString.empty()) {
        return;
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
    //Clear the vertices
    for (auto& sVA : sizedVertexArrays) {
        sVA.vertices.clear();
    }
    //Set the first glyphPos to the top left corner of mText
    Vector2f glyphPos = pos + Vector2f(0, size.y / 2.f);
    unsigned int glyphSize = static_cast<unsigned int>(round(size.y));

    for (const auto& c : wString) {
        //Apply any formatting transforms
        glyphPos.x += transformsToApply.x;
        glyphPos.y += transformsToApply.y;
        glyphSize += static_cast<unsigned int>(transformsToApply.z);
        //Reset the transforms
        transformsToApply = { 0.f, 0.f, 0.f };

        //Clip of the end of text if it goes outside the bounds width
        if (glyphPos.x > size.x) {
            break;
        }
        const Glyph& glyph = font->getGlyph(static_cast<Uint32>(c), glyphSize, false);
        //Skip the glyph if FormatGlyph() returns false
        if (!FormatGlyph(c, glyphPos, glyphSize)) {
            //Don't add the glyph if it is just whitespace
            if (c != ' ') {
                AddGlyph(glyph, glyphPos, glyphSize, fillColor);
            }
            //Position the next glyph in front of the last
            glyphPos.x += glyph.advance;
        }
    }
}

void MText::UpdateKeywords()
{
    for (const auto& keyword : keywords) {
        size_t found = wString.find(keyword.first);
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
    const Vector2f padding(1.f, 1.f);
    const FloatRect bounds = glyph.bounds;
    const IntRect textureRect = glyph.textureRect;

    const Vector2f p1 = bounds.getPosition() - padding;
    const Vector2f p2 = bounds.getPosition() + bounds.getSize() + padding;

    const auto uv1 = Vector2f(textureRect.getPosition()) - padding;
    const auto uv2 = Vector2f(textureRect.getPosition() + textureRect.getSize()) + padding;

    //Find the associated vertex array
    VertexArray* vertices = nullptr;
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
            return true;
        case '^':
            //Add power to the nest
            nest.push(Format::power);
            //Format the following text to be a power
            FormatPower(true, glyphPos, glyphSize);
            return true;
        case L'\u221A':
            //Add square root to the nest
            nest.push(Format::sqrt);
            //Format the following text to be under square root
            FormatSquareRoot(true, glyphPos, glyphSize);
            return false;
        case ']':
            //If it is the second ] in ]] do nothing
            if (skipEscapeCharacter) {
                skipEscapeCharacter = false;
                return true;
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
                    return true;
                }
                //Pop the stack
                nest.pop();
                
                skipEscapeCharacter = true;
            }
            return true;
    }
    return false;
}

void MText::FormatPower(const bool start, const Vector2f glyphPos, const unsigned int glyphSize)
{
    float fGlyphSize = static_cast<float>(glyphSize);
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
    if (start) {
        fillColor = Color::Red;
    }

    else {
        fillColor = Color::White;
    }
}
