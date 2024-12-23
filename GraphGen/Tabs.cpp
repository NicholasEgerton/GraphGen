//Work of Nicholas Egerton
#include "Tabs.h"
#include <vector>
#include <iomanip>
#include "Utils.h"

using namespace sf;

Tabs::Tabs(Vector2f pos, Vector2f size, int amount, Color tabCol, Color textCol, unsigned int textSize, Font& font, InputText& aInputText, InputText& nInputText, InputText& cInputText, Slider& aSlider, Slider& nSlider, Slider& cSlider, RenderWindow& window)
	: originalSize(size), originalColor(tabCol), tabsAmount(amount), aInputText(&aInputText), nInputText(&nInputText), cInputText(&cInputText),
	aSlider(&aSlider), nSlider(&nSlider), cSlider(&cSlider), window(&window)
{
	float lastX = 0;

	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

	for(int i = 0; i < amount; i++) {
		//TEXT 
		std::string s;

		s.push_back(alphabet[i]);
		s.append("(x)");

		Tab tab = {
			RectangleShape(size),
			Text(s, font, textSize),
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
			if (Utils::InBounds(Mouse::getPosition(*window), tabs[i].rect.getPosition(), tabs[i].rect.getSize())) {
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
	if (!Utils::IsStringNum(aString) || !Utils::IsStringNum(nString) || !Utils::IsStringNum(cString)) {
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
		Utils::FloatToString(tabs[i].a, aInputText->GetMaxChar()),
		Utils::FloatToString(tabs[i].n, nInputText->GetMaxChar()),
		Utils::FloatToString(tabs[i].c, cInputText->GetMaxChar())
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

void Tabs::Draw()
{
	for (int i = 0; i < tabsAmount; i++) {
		window->draw(tabs[i].rect);
		window->draw(tabs[i].text);
	}
}

