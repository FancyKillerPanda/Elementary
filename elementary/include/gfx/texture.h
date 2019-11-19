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

public:
	Texture(SDL_Renderer* renderer, std::string filepath);
	~Texture();

	void draw();

	void setPosition(int x, int y);
	void setRect(int x, int y, int width, int height);
};

}
