#pragma once

#include <string>

#include <SDL/SDL.h>

namespace el
{

class Window
{
public:
	bool isInitialised = false;

	// Window properties
	int width;
	int height;
	std::string title;

	// SDL data
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;

public:
	Window() = default;
	Window(int width, int height, std::string title);
};

}
