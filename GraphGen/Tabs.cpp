#include "Tabs.h"
#include <vector>
#include <iomanip>

Tabs::Tabs(Vector2f pos, Vector2f size, int amount, Color tabCol, Color textCol, unsigned int textSize, Font* font, InputText* aInputText, InputText* nInputText, InputText* cInputText, Slider* aSlider, Slider* nSlider, Slider* cSlider, RenderWindow* window)
{
	//Setup received variables
	Tabs::window = window;
	Tabs::tabsAmount = amount;
	Tabs::originalSize = size;
	Tabs::originalColor = tabCol;
	Tabs::aInputText = aInputText;
	Tabs::nInputText = nInputText;
	Tabs::cInputText = cInputText;
	Tabs::aSlider = aSlider;
	Tabs::nSlider = nSlider;
	Tabs::cSlider = cSlider;

	float lastX = 0;

	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

	for(int i = 0; i < amount; i++) {
		//TEXT 
		std::string s;

		s.push_back(alphabet[i]);
		s.append("(x)");

		Tab tab = {
			RectangleShape(size),
			Text(s, *font, textSize),
			false,
			1.f,
			1.f,
			0.f,
		};

		tabs.push_back(tab);

		//Last X is the x value of the end of the last rectangle
		//By doing pos.x + lastX it adds the start of the tabs to the most recent one
		//In doing this, the position (top left of rect) will be evenly stacked at the
		//End of last
		Vector2f rectPos = Vector2f(pos.x + lastX, pos.y);
		tabs[i].rect.setPosition(rectPos);

		tabs[i].rect.setFillColor(tabCol);
		//Sets the outline color to the inverse of fill
		tabs[i].rect.setOutlineColor(Color(255 - tabCol.r, 255 - tabCol.g, 255 - tabCol.b));
		tabs[i].rect.setOutlineThickness(5);

		Vector2f textPos = Vector2f(pos.x + lastX, pos.y - textSize / 5);

		tabs[i].text.setPosition(textPos);
		tabs[i].text.setFillColor(textCol);

		//Set the first by default to be selected
		if (i == 0) {
			tabs[i].rect.setSize(Vector2f(originalSize.x, originalSize.y + 10));
			tabs[i].clicked = true;
		}

		lastX = rectPos.x + size.x;
	}
}

void Tabs::Update(Event event)
{
	//If mouse is over rect, increase the size of y to indent like a tab
	for (int i = 0; i < tabsAmount; i++) {
		//Don't check if rect has already been clicked
		if (!tabs[i].clicked) {

			//Check if mouse is over tab
			if (InBounds(Mouse::getPosition(*window), tabs[i].rect.getPosition(), tabs[i].rect.getSize())) {
				tabs[i].rect.setSize(Vector2f(originalSize.x, originalSize.y + 10));

				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
					//Reset all other
					//clicked vector values to false
					for (int x = 0; x < tabsAmount; x++) {
						tabs[x].clicked = false;
					}
					tabs[i].clicked = true; //Set this rect clicked to true

					//Click effect
					tabs[i].rect.setFillColor(originalColor + Color(50, 50, 50));

					//Set text values to the saved a, n and c values
					UpdateText(i);
				}
			}

			//Reset the rect if its not clicked and not hovered
			else {
				tabs[i].rect.setSize(originalSize);

				tabs[i].rect.setFillColor(originalColor);
			}

		}

		//If it has been clicked
		else {
			UpdateValues(i);
			tabs[i].rect.setFillColor(originalColor);
		}
	}
}


bool Tabs::InBounds(Vector2i pointPos, Vector2f boundPos, Vector2f boundSize)
{
	//Keeping in mind that the position of a rectangle is defined by its top left corner,
	//And the size increases from the top left corner
	//Checking if the point is > than the position and less than the size of the rect + position
	//Gives if the point is in the rect
	if (pointPos.x >= boundPos.x && pointPos.y >= boundPos.y) {
		if (pointPos.x <= boundPos.x + boundSize.x && pointPos.y <= boundPos.y + boundSize.y) {
			return true;
		}
	}

	return false;
}

bool Tabs::IsNum(std::string string) {
	
	for (int i = 0; i < string.length(); i++) {
		if (!isdigit(string[i])) {
			if (string[i] == '-') {
				if (i != 0 || string.length() <= 1) {
					return false;
				}
			}

			else if (string[i] == '.') {
				if (string.find_first_of('.') != string.find_last_of('.') || string.length() <= 1) {
					return false;
				}

				else if (string[i - 1] == '-') {
					return false;
				}
			}

			else {
				return false;
			}
		}
	}

	return true;
}

void Tabs::UpdateValues(int i)
{
	std::string aString = static_cast<std::string>(aInputText->GetText().getString());
	std::string nString = static_cast<std::string>(nInputText->GetText().getString());
	std::string cString = static_cast<std::string>(cInputText->GetText().getString());

	//Don't generate if strings are empty
	if (aString.empty() || nString.empty() || cString.empty()) {
		return;
	}

	//Don't generate if strings are not a valid number
	if (!IsNum(aString) || !IsNum(nString) || !IsNum(cString)) {
		return;
	}

	//Don't generate if values have not changed
	if (tabs[i].a == std::stof(aString) && tabs[i].n == std::stof(nString) && tabs[i].c == std::stof(cString)) {
		return;
	}

	aSlider->ChangeBeamPos();
	nSlider->ChangeBeamPos();
	cSlider->ChangeBeamPos();

	tabs[i].a = std::stof(aString);
	tabs[i].n = std::stof(nString);
	tabs[i].c = std::stof(cString);
}

void Tabs::UpdateText(int i)
{

	std::string strArr[3] = {
		FloatToString(tabs[i].a, aInputText->GetMaxChar()),
		FloatToString(tabs[i].n, nInputText->GetMaxChar()),
		FloatToString(tabs[i].c, cInputText->GetMaxChar())
	};

	//REMOVE TRAILING ZEROS

	//Loop through the 3 params, a, n and c
	
	for (int i = 0; i < 3; i++) {
		if (strArr[i].find('.') != std::string::npos)
		{
			//Set the string to a substring of the current string
			//But only include from start to the last non zero digit after
			strArr[i] = strArr[i].substr(0, strArr[i].find_last_not_of('0') + 1);
			
			//Get rid of decimal point if last character
			if (strArr[i].find('.') == strArr[i].size() - 1)
			{
				strArr[i].pop_back();
			}
		}
	}

	aInputText->SetTextString(strArr[0]);
	nInputText->SetTextString(strArr[1]);
	cInputText->SetTextString(strArr[2]);

	aSlider->ChangeBeamPos();
	nSlider->ChangeBeamPos();
	cSlider->ChangeBeamPos();
}

std::string Tabs::FloatToString(float f, int precision)
{
	std::stringstream stream;

	stream << std::fixed << std::setprecision(precision) << f;

	std::string newStr = stream.str();

	return newStr;
}

void Tabs::Draw()
{
	for (int i = 0; i < tabsAmount; i++) {
		window->draw(tabs[i].rect);
		window->draw(tabs[i].text);
	}
}

