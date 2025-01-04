#include "UI/MText.h"

using namespace sf;

MText::MText(Vector2f pos, Vector2f size, const Font& font, std::wstring defaultText) : Widget(pos, size), font(font), wString(defaultText)
{
    //Push back the default sized vertex array
    //More can be added later on, to support the textures
    //Of smaller glyphs
    sizedVertexArrays.push_back({ VertexArray(Triangles), static_cast<unsigned int>(round(size.y))});
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
        states.texture = &font.getTexture(sVA.size);
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
        //Clip of the end of text if it goes outside the bounds width
        if (glyphPos.x > size.x) {
            break;
        }
        const Glyph& glyph = font.getGlyph(static_cast<Uint32>(c), glyphSize, false);
        //Don't add the glyph if it is just whitespace
        if (c != ' ') {
            AddGlyph(glyphPos, glyphSize, glyph, Color::White);
        }
        //Position the next glyph in front of the last
        glyphPos.x += glyph.advance;
        glyphSize--;
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

void MText::AddGlyph(const sf::Vector2f glyphPos, const unsigned int glyphSize, const sf::Glyph& glyph, const sf::Color& color)
{
    //This function is very similar to sf::Text::addGlyphQuad(), just
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
    vertices->append({ glyphPos + sf::Vector2f(p1.x, p1.y), color, {uv1.x, uv1.y} });
    vertices->append({ glyphPos + sf::Vector2f(p2.x, p1.y), color, {uv2.x, uv1.y} });
    vertices->append({ glyphPos + sf::Vector2f(p1.x, p2.y), color, {uv1.x, uv2.y} });
    vertices->append({ glyphPos + sf::Vector2f(p1.x, p2.y), color, {uv1.x, uv2.y} });
    vertices->append({ glyphPos + sf::Vector2f(p2.x, p1.y), color, {uv2.x, uv1.y} });
    vertices->append({ glyphPos + sf::Vector2f(p2.x, p2.y), color, {uv2.x, uv2.y} });
}
