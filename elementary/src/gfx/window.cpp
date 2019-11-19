#include "gfx/window.h"
#include "utils/log.h"

namespace el
{

Window::Window(int width, int height, std::string title)
	: width(width), height(height), title(title)
{
	// Window init
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (!window)
	{
		sdlError("Failed to create window.");
		return;
	}

	// Renderer init
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
	{
		sdlError("Failed to create renderer.");
		return;
	}

	// Sets renderer properties
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	isInitialised = true;
}

}
