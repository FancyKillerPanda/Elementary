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
	Text(SDL_Renderer* renderer, std::string fontPath, std::string text, unsigned int size, SDL_Color colour);

	void update();
	void update(std::string fontPath);
	void draw();

	// NOTE(fkp): Returns true if text was clicked, false otherwise
	bool handleEvent(const SDL_Event& event);

	void setPosition(int x, int y);
	void setColourValues(SDL_Color p_BaseColour, SDL_Color p_HoverColour, SDL_Color p_PressedColour);
	void setIsClickable(bool value);

	inline bool getIsClickable() { return texture.isClickable; }
};
	
}
