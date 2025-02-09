//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include <memory>

class Renderer {
public:
	Renderer();

	bool IsOpen();
	bool PollEvent(sf::Event& event);
	void Draw(const sf::Drawable& obj, const sf::RenderStates states = sf::RenderStates::Default);
	void Display();
	void Clear(const sf::Color color = sf::Color());
	void Close();
	void SetView(const sf::View& view);
	void SetCursor(const sf::Cursor::Type cursorType);
private:
	//Set the window size to half the resolution
	sf::RenderWindow window{ sf::VideoMode((sf::VideoMode::getDesktopMode().width + 1) / 2, (sf::VideoMode::getDesktopMode().height + 1) / 2), "GraphGen" };
	sf::Font cambria;

	sf::Cursor arrowCursor;
	sf::Cursor textCursor;
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