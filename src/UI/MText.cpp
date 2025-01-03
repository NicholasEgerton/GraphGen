#include "UI/MText.h"

using namespace sf;

MText::MText(Vector2f pos, Vector2f size, const Font& font, std::wstring defaultText) : Widget(pos, size), font(font), wString(defaultText)
{
    UpdateVertices();
}

void MText::draw(RenderTarget& target, RenderStates states) const
{
    if (vertices.getVertexCount() <= 0 || wString.empty()) {
        return;
    }
    //Set the states texture to the font's so that the characters
    //Are rendered correctly
    states.texture = &font.getTexture(static_cast<unsigned int>(round(size.y)));
    target.draw(vertices, states);
}

void MText::UpdateVertices()
{
    vertices.clear();
    //Set the first glyphPos to the top left corner of mText
    Vector2f glyphPos = pos + Vector2f(0, size.y / 2.f);
    for (const auto& c : wString) {
        const Glyph& glyph = font.getGlyph(static_cast<Uint32>(c), static_cast<unsigned int>(round(size.y)), false);
        //Don't add the glyph if it is just whitespace
        if (c != ' ') {
            AddGlyph(glyphPos, glyph, Color::White);
        }
        //Position the next glyph in front of the last
        glyphPos.x += glyph.advance;
    }
}

void MText::AddGlyph(sf::Vector2f position, const sf::Glyph& glyph, const sf::Color& color)
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

    vertices.append({ position + sf::Vector2f(p1.x, p1.y), color, {uv1.x, uv1.y} });
    vertices.append({ position + sf::Vector2f(p2.x, p1.y), color, {uv2.x, uv1.y} });
    vertices.append({ position + sf::Vector2f(p1.x, p2.y), color, {uv1.x, uv2.y} });
    vertices.append({ position + sf::Vector2f(p1.x, p2.y), color, {uv1.x, uv2.y} });
    vertices.append({ position + sf::Vector2f(p2.x, p1.y), color, {uv2.x, uv1.y} });
    vertices.append({ position + sf::Vector2f(p2.x, p2.y), color, {uv2.x, uv2.y} });
}
