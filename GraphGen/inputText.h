//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"

class InputText {
public:
	InputText() = default;
	InputText(sf::Vector2f pos, sf::Vector2f size, unsigned int textSize,
		sf::String defaultText, int maxChar, sf::Color textCol, 
		sf::Color backgroundCol, sf::Sprite& iBeam, sf::Font& font, 
		sf::RenderWindow& window);
	virtual void Update(sf::Event event);
	void Draw();

protected:


	sf::Text text;
	sf::RectangleShape rect;

	//Received protected variables
	int maxChar;

private:
	virtual sf::String ValidText(sf::Event event, sf::String s);


	bool inRect = false;
	bool clickedRect = false;


	//Received private variables
	sf::RenderWindow* window{};

	sf::Sprite* iBeam{};

public:

	const sf::Text& GetText() {
		return text;
	}

	void SetTextString(sf::String s) {
		text.setString(s);
	}

	const int& GetMaxChar() {
		return maxChar;
	}
};