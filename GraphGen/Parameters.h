#pragma once

#include "SFML/Graphics.hpp"
#include "InputText.h"
#include "slider.h"
#include "Button.h"

using namespace sf;

class Parameters {

public:
	void Init(RenderWindow* mainWindow, Sprite* iBeam, Font* Roboto);
	void Update();
	void Generate(Vector2i defaultWindowSize);

	float a;
	float n;
	float c;

	VertexArray lines1;
	VertexArray lines2;
	bool asymptote;

private:

	Vector2f ConvertPos(Vector2i defaultWindowSize, int x, int y);

	void CalculateLines(Vector2i defaultWindowSize);

	bool IsNum(std::string string);

	Clock clock;

	RenderWindow window;

	//If singular functions
	Text titleText;
	Text infoText;
	Text linearText;
	Text aText;
	Text nText;
	Text cText;

	InputText aInputText;
	InputText nInputText;
	InputText cInputText;

	Slider aSlider;
	Slider nSlider;
	Slider cSlider;

	Button aButton;

	//Received variables
	RenderWindow* mainWindow;
	Event event;

	Sprite* iBeam;

	Font* Roboto;
};