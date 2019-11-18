#include <cstdio>
#include <cstdarg>

#include <SDL/SDL.h>

#include "utils/log.h"

void error(const char* msg, ...)
{
	std::va_list args;
	va_start(args, msg);
	
	std::fprintf(stderr, "Error: ");
	std::vfprintf(stderr, msg, args);
	std::fprintf(stderr, "\n");

	va_end(args);
}

void sdlError(const char* msg, ...)
{
	std::va_list args;
	va_start(args, msg);
	
	std::fprintf(stderr, "Error: ");
	std::vfprintf(stderr, msg, args);
	std::fprintf(stderr, "\nSDL_Error: %s\n", SDL_GetError());

	va_end(args);
}
