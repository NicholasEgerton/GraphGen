#pragma once

#include "SFML/Graphics.hpp"
#include "InputText.h"
#include "slider.h"
#include "Button.h"
#include "Tabs.h"
#include "FunctionInputText.h"

using namespace sf;

class Parameters {

public:
	Parameters(RenderWindow* mainWindow, Sprite* iBeam, Font* Roboto);

	void Update();
	void Generate(Vector2i defaultWindowSize, bool ignoreSame);

private:

	Vector2f ConvertPos(Vector2f defaultWindowSize, float x, float y);

	void CalculateLines(Vector2f defaultWindowSize);

	struct Vector2iComparator {
		bool operator()(const Vector2i& v1, const Vector2i& v2) const {
			return v1.x < v2.x;
		}
	};

	bool IsNum(std::string string);

	float CalculateY(float x);

	bool mode = false; //False = singular, true = composite functions

	float scale = 1;

	std::vector<VertexArray> linesVector;

	//For singular functions only
	float a;
	float n;
	float c;

	//For composite functions only
	std::vector<int> indexes;
	std::vector<Vector3f> aNCValues = { Vector3f(1, 1, 0) };
	//Note: in mathOperations 0 = /, 1 = *, 2 = +, 3 = -
	//This is so it can be sorted easily for bidmas
	//And the second parameter is the original index of the operator

	std::vector<Vector2i> mathOperations;

	const static int maxOperators = 8;

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

	FunctionInputText functionInputText;

	Slider aSlider;
	Slider nSlider;
	Slider cSlider;

	Button aButton;
	Button modeButton;

	Tabs tabs;

	//Received variables
	RenderWindow* mainWindow;
	Event event;

	Sprite* iBeam;

	Font* Roboto;

public:
	const std::vector<VertexArray>& GetLinesVector() {
		return linesVector;
	}

	const float& GetScale() {
		return scale;
	}

	void SetScale(float f) {
		scale = f;
	}
};