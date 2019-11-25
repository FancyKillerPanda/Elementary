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

	// Text that appears when there is no characters
	std::string defaultText = {};

	bool numbersOnly = false;
	bool isSelected = false;
	bool centerAlign = true;

public:
	InputText(SDL_Renderer* renderer, std::string fontPath, std::string defaultText = "Text", unsigned int size = 32, SDL_Color colour = SDL_Color { 255, 255, 255, 255 });

	void handleEvent(SDL_Event& event);
	void draw();
};
	
}
