#pragma once

#include <vector>

#include <SDL/SDL.h>

#include "gfx/text.h"

namespace el
{

class Menu
{
public:
	std::vector<Text> items;

	SDL_Color baseColour;
	SDL_Color hoverColour;
	SDL_Color pressedColour;
	SDL_Color selectedColour;

	int itemIndexHovering = -1;
	int itemIndexSelected = -1;

	// Key usage for controlling the menu
	bool canUseLeftRightKeys = false;
	bool canUseUpDownKeys = false;

	// If this is set, the selected item will remain coloured
	bool hasRadioButtons = false;
	bool canUncheckRadioButtons = false;

public:
	Menu(std::vector<Text> texts);
	Menu(std::vector<Text> texts, SDL_Color baseColour, SDL_Color hoverColour, SDL_Color pressedColour);
	Menu(std::vector<Text> texts, SDL_Color baseColour, SDL_Color hoverColour, SDL_Color pressedColour, SDL_Color selectedColour);

	void draw();
	// NOTE(fkp): Returns the index of the item that was clicked, -1 if nothing was
	int handleEvent(const SDL_Event& event);

	void setPositionsHorizontal(int x, int y, int distanceBetweenItemCenters, bool setUseLeftRightKeys = true);
	void setPositionsVertical(int x, int y, int distanceBetweenItemCenters, bool setUseUpDownKeys = true);
	void setColourValues(SDL_Color p_BaseColour, SDL_Color p_HoverColour, SDL_Color p_PressedColour);
};
	
}
