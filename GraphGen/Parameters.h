//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "InputText.h"
#include "slider.h"
#include "Button.h"
#include "Tabs.h"
#include "FunctionInputText.h"

class Parameters {

public:
	Parameters() = default;
	Parameters(sf::RenderWindow& mainWindow, sf::Sprite& iBeam, sf::Font& font);

	void Update();
	void Generate(sf::Vector2i defaultWindowSize, bool ignoreSame);

private:

	sf::Vector2f ConvertPos(sf::Vector2f defaultWindowSize, float x, float y);

	void CalculateLines(sf::Vector2f defaultWindowSize);

	struct Vector2iComparator {
		bool operator()(const sf::Vector2i& v1, const sf::Vector2i& v2) const {
			return v1.x < v2.x;
		}
	};

	float CalculateY(float x);

	bool mode = false; //False = singular, true = composite functions

	float scale = 1;

	std::vector<sf::VertexArray> linesVector;

	//For singular functions only
	float a;
	float n;
	float c;

	//For composite functions only
	std::vector<int> indexes;
	std::vector<sf::Vector3f> aNCValues = { sf::Vector3f(1, 1, 0) };
	//Note: in mathOperations 0 = /, 1 = *, 2 = +, 3 = -
	//This is so it can be sorted easily for bidmas
	//And the second parameter is the original index of the operator

	std::vector<sf::Vector2i> mathOperations;

	const static int maxOperators = 8;

	sf::Clock clock;

	sf::RenderWindow window;

	sf::Text titleText;
	sf::Text infoText;
	sf::Text linearText;
	sf::Text aText;
	sf::Text nText;
	sf::Text cText;

	InputText aInputText;
	InputText nInputText;
	InputText cInputText;

	FunctionInputText functionInputText;

	Slider aSlider;
	Slider nSlider;
	Slider cSlider;

	Button aButton;
	Button modeButton;

	Tabs tabs;

	sf::Event event;

	//Received variables
	sf::RenderWindow* mainWindow{};

	sf::Sprite* iBeam{};

	sf::Font* font{};

public:
	const std::vector<sf::VertexArray>& GetLinesVector() {
		return linesVector;
	}

	const float& GetScale() {
		return scale;
	}

	void SetScale(float f) {
		scale = f;
	}
};