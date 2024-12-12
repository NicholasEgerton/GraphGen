//Work of Nicholas Egerton
#pragma once

#include "SFML/Graphics.hpp"
#include "InputText.h"
#include "slider.h"
#include "Button.h"
#include "Tabs.h"
#include "FunctionInputText.h"
#include <array>

class Parameters {

public:
	Parameters() = default;
	Parameters(sf::RenderWindow& mainWindow, sf::Sprite& iBeam, sf::Font& font);

	void Update();
	void Generate(sf::Vector2i defaultWindowSize, bool ignoreSame);

private:

	sf::Vector2f ConvertPos(sf::Vector2f defaultWindowSize, float x, float y);

	std::vector<std::string> InfixToPostfix(std::string& infix);

	void CalculateLines(sf::Vector2f defaultWindowSize);

	bool ValidateInfix(std::string& infix);

	int GetOperatorPriority(char op) {
		if (op == '*' || op == '/') {
			return 1; //Highest priority
		}

		else if (op == '+' || op == '-') {
			return 0; //Lowest priority
		}

		else {
			return -1; //Invalid operator
		}
	}

	float CalculateY(float x);

	bool mode = false; //False = singular, true = composite functions

	float scale = 1;

	std::vector<sf::VertexArray> linesVector;

	//For singular functions only
	float a;
	float n;
	float c;

	//For composite functions only
	std::vector<std::string> postfixExpression;
	std::string oldInfix = "a(x)";

	struct ANC {
		float a;
		float n;
		float c;
	};

	std::array<ANC, 8> aNCValues;


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