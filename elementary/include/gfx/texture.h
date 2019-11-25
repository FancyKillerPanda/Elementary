#pragma once

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace el
{

enum class TextureClickState
{
	None,		// Mouse not over the texture
	Hover,		// On mouse over
	Pressed,	// On mouse down
	Clicked		// On mouse up
};

class Texture
{
public:
	bool isInitialised = false;
	SDL_Renderer* renderer;

	std::string filepath;
	SDL_Texture* texture = nullptr;
	SDL_Rect rect = {};

	bool isClickable = false;
	TextureClickState currentClickState = TextureClickState::None;

private:
	TextureClickState lastClickState = TextureClickState::None;

public:
	Texture(SDL_Renderer* renderer);
	Texture(SDL_Renderer* renderer, std::string filepath);
	~Texture();

	void convertFromSurface(SDL_Surface* surfaceToConvertFrom);
	void draw();

	// NOTE(fkp): Returns true if texture click state has changed
	bool handleEvent(const SDL_Event& event);

	void setTopLeft(int x, int y);
	void setCenter(int x, int y);
	void setRect(int x, int y, int width, int height);

	SDL_Point getCenter();
};

}
