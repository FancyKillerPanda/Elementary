#pragma once

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace el
{

class Texture
{
public:
	bool isInitialised = false;
	SDL_Renderer* renderer;

	std::string filepath;
	SDL_Texture* texture = nullptr;
	SDL_Rect rect = {};

	bool isClickable = false;

public:
	Texture(SDL_Renderer* renderer);
	Texture(SDL_Renderer* renderer, std::string filepath);
	~Texture();

	void convertFromSurface(SDL_Surface* surfaceToConvertFrom);
	void draw();

	// TODO(fkp): Make this return some sort of mouse state
	// NOTE(fkp): Returns true if button clicked
	bool handleEvent(const SDL_Event& event);

	void setPosition(int x, int y);
	void setRect(int x, int y, int width, int height);
};

}
