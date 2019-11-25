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

	// Text value
	std::string text;

	// Colours
	SDL_Color baseColour;
	SDL_Color selectedColour;

	// Text that appears when there is no characters
	std::string defaultText = {};

	bool numbersOnly = false;
	bool centerAlign = true;
	bool isShowingDefaultText = true;

private:
	bool isSelected = false;
	SDL_Point centerPos = { 0, 0 };
	
	// Text that is being displayed
	Text displayedText;

public:
	InputText(SDL_Renderer* renderer, std::string fontPath, std::string defaultText = "Text", unsigned int size = 32, SDL_Color colour = SDL_Color { 255, 255, 255, 255 });

	void handleEvent(SDL_Event& event);
	void draw();

	void setCenter(int x, int y);
	void setIsSelected(bool value);
	
	inline bool getIsSelected() { return isSelected; }
};
	
}
