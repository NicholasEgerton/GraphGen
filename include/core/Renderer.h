//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include <memory>

class Renderer {
public:
	Renderer();

	bool IsOpen();
	bool PollEvent(sf::Event& event);
	void Draw(const sf::Drawable& obj);
	void Display();
	void Clear(const sf::Color color = sf::Color());
	void Close();
	void Resize(const sf::Vector2u newSize);
	void SetCursor(const sf::Cursor::Type cursorType);
private:
	static const sf::Vector2u defaultWindowSize;

	sf::RenderWindow window{ sf::VideoMode(defaultWindowSize.x, defaultWindowSize.y), "GraphGen" };
	sf::View view{ window.getDefaultView() };
	sf::Font cambria;

	sf::Cursor arrowCursor;
	sf::Cursor textCursor;
public:
	const sf::Font& GetCambria() const {
		return cambria;
	}
};