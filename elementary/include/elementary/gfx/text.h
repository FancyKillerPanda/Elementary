#pragma once

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "gfx/texture.h"

namespace el
{

class Text
{
public:
	bool isInitialised = false;

	std::string fontPath;
	TTF_Font* font = nullptr;
	SDL_Renderer* renderer = nullptr;
	Texture texture;

	std::string text;
	unsigned int size;

	SDL_Color currentColour;
	SDL_Color baseColour;
	SDL_Color hoverColour;
	SDL_Color pressedColour;

public:
	Text() = default;
	Text(SDL_Renderer* renderer, std::string fontPath, std::string text, unsigned int size, SDL_Color colour = { 255, 255, 255, 255 });

	void update();
	void update(std::string fontPath);
	void draw();

	// NOTE(fkp): Returns true if text was clicked, false otherwise
	bool handleEvent(const SDL_Event& event);

	void setTopLeft(int x, int y);
	void setCenter(int x, int y);
	void setIsClickable(bool value);
	void setColourValues(SDL_Color p_BaseColour, SDL_Color p_HoverColour, SDL_Color p_PressedColour);
	void setCurrentColour(SDL_Color colour);

	inline bool getIsClickable() const { return texture.isClickable; }
	inline SDL_Point getCenter() const { return texture.getCenter(); }
};
	
}
