//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"

class Renderer {
public:
	Renderer();

	void Draw(sf::Drawable& obj);
	void Display();
	void Clear();
	void Close();
	void Resize(sf::Vector2f newSize);
private:
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<sf::View> view;
	std::unique_ptr<sf::Font> cambria;
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