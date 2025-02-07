//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include <memory>

class Renderer {
public:
	Renderer();

	void Draw(const sf::Drawable& obj);
	void Display();
	void Clear();
	void Close();
	void Resize(const sf::Vector2u newSize);
	void SetCursor(const sf::Cursor::Type cursorType);

	static const sf::Vector2u defaultWindowSize;
private:
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<sf::View> view;
	std::unique_ptr<sf::Font> cambria;

	sf::Cursor arrowCursor;
	sf::Cursor textCursor;
public:
	sf::RenderWindow* GetWindow() const {
		return window.get();
	}

	sf::View* GetView() const {
		return view.get();
	}

	sf::Font* GetCambria() const {
		return cambria.get();
	}
};