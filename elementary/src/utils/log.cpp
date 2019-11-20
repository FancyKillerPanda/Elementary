#include <cstdio>
#include <cstdarg>

#if defined(ELEMENTARY_WIN32)
#include <windows.h>
#endif

#include <SDL/SDL.h>

#include "utils/log.h"
#include "utils/console_colour.h"

namespace el
{

void info(const char* msg, ...)
{
#if defined(ELEMENTARY_DEBUG)
	std::va_list args;
	va_start(args, msg);
	
	ConsoleColour::white();
	std::printf("Info: ");
	ConsoleColour::reset();
	std::vprintf(msg, args);
	std::printf("\n");

	va_end(args);
#endif
}

void warn(const char* msg, ...)
{
#if defined(ELEMENTARY_DEBUG)
	std::va_list args;
	va_start(args, msg);
	
	ConsoleColour::yellow();
	std::printf("Warning: ");
	ConsoleColour::reset();
	std::vprintf(msg, args);
	std::printf("\n");

	va_end(args);
#endif
}

void error(const char* msg, ...)
{
#if defined(ELEMENTARY_DEBUG)
	std::va_list args;
	va_start(args, msg);
	
	ConsoleColour::red();
	std::fprintf(stderr, "Error: ");
	ConsoleColour::reset();
	std::vfprintf(stderr, msg, args);
	std::fprintf(stderr, "\n");

	va_end(args);
#endif
}

void sdlError(const char* msg, ...)
{
#if defined(ELEMENTARY_DEBUG)
	std::va_list args;
	va_start(args, msg);
	
	ConsoleColour::red();
	std::fprintf(stderr, "Error: ");
	ConsoleColour::reset();
	std::vfprintf(stderr, msg, args);
	std::fprintf(stderr, "\nSDL_Error: %s\n", SDL_GetError());

	va_end(args);
#endif
}

}
