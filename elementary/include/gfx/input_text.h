#pragma once

#include <SDL/SDL.h>

#include "gfx/text.h"

namespace el
{

class InputText
{
public:
	bool isInitialised = false;
	SDL_Renderer* renderer = nullptr;

	// Text that is being displayed
	Text currentText;

	// Colours
	SDL_Color baseColour;
	SDL_Color selectedColour;

	// Text that appears when there is no characters
	std::string defaultText = {};

	bool numbersOnly = false;
	bool centerAlign = true;

private:
	bool isSelected = false;

public:
	InputText(SDL_Renderer* renderer, std::string fontPath, std::string defaultText = "Text", unsigned int size = 32, SDL_Color colour = SDL_Color { 255, 255, 255, 255 });

	void handleEvent(SDL_Event& event);
	void draw();

	void setIsSelected(bool value);
	inline bool getIsSelected() { return isSelected; }
};
	
}
