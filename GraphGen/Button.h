//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"

class Button {
public:
	Button() = default;
	Button(sf::Vector2f pos, sf::Vector2f size, sf::Color buttonCol, 
		sf::Color textCol, unsigned int textSize, sf::String defaultText1,
		sf::String defaultText2, sf::Font& font, sf::RenderWindow& window);
	void Update(sf::Event event);
	void Draw();

private:

	sf::RectangleShape rect;
	sf::Text text;

	bool state = false;

	bool highlight = false;

	//Received variables
	sf::RenderWindow* window{};
	sf::String defaultText1{};
	sf::String defaultText2{};

	sf::Color buttonCol{};

public:

	const bool& GetState() {
		return state;
	}
};