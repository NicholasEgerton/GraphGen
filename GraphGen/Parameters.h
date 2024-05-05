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

	Vertex* lines;
	int lineDensity;

private:

	Vector2f ConvertPos(Vector2i defaultWindowSize, int x, int y);

	bool IsNum(std::string string);

	Clock clock;

	RenderWindow window;

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