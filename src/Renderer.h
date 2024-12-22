//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"

class Renderer {
public:
	Renderer();

	void Draw(const sf::Drawable& obj);
	void Display();
	void Clear();
	void Close();
	void Resize(const sf::Vector2f newSize);
	void SetCursor(const sf::Cursor::Type cursorType);
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