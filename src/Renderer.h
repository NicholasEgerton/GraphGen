//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"

class Renderer {
public:
	Renderer(std::unique_ptr<sf::RenderWindow> window);
	void Update();

private:
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<sf::View> view;

public:
	sf::RenderWindow* GetWindow() const {
		return window.get();
	}

	sf::View* GetView() const {
		return view.get();
	}
};