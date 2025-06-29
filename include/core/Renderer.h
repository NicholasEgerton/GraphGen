#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window/Cursor.hpp"
#include <memory>

class Renderer {
public:
	Renderer();

	bool IsOpen();
	std::optional<sf::Event> PollEvent();
	void Draw(const sf::Drawable& obj, const sf::RenderStates states = sf::RenderStates::Default);
	void Display();
	void Clear(const sf::Color color = sf::Color());
	void Close();
	void SetView(const sf::View& view);
	void SetCursor(const sf::Cursor::Type cursorType);
private:
	sf::RenderWindow window;
	sf::Font cambria;

	sf::Cursor arrowCursor{ sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value() };
	sf::Cursor textCursor{ sf::Cursor::createFromSystem(sf::Cursor::Type::Text).value() };
public:
	/// <summary>
	/// Get the font "Cambria."
	/// </summary>
	const sf::Font& GetCambria() const {
		return cambria;
	}
	/// <summary>
	/// Get the size of the window.
	/// </summary>
	const sf::Vector2u GetSize() const {
		return window.getSize();
	}
};