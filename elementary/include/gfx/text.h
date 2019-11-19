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
	SDL_Color colour;

public:
	Text(SDL_Renderer* renderer, std::string fontPath, std::string text, unsigned int size, SDL_Color colour);

	void update();
	void update(std::string fontPath);
	void draw();

	void setPosition(int x, int y);
};
	
}
