#include "utils/log.h"
#include "gfx/texture.h"

namespace el
{

Texture::Texture(SDL_Renderer* renderer, std::string filepath)
	: renderer(renderer), filepath(filepath)
{
	texture = IMG_LoadTexture(renderer, filepath.c_str());

	if (!texture)
	{
		sdlError("Failed to create texture (filepath: %s).", filepath.c_str());
		return;
	}

	if (SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) != 0)
	{
		sdlError("Texture is invalid (filepath: %s).", filepath.c_str());
		return;
	}

	isInitialised = true;
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

void Texture::draw()
{
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Texture::setPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Texture::setRect(int x, int y, int width, int height)
{
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
}

}
