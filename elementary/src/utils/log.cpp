#include <cstdio>
#include <cstdarg>

#if defined(ELEMENTARY_WIN32)
#include <windows.h>
#endif

#include <SDL/SDL.h>

#include "utils/log.h"

void error(const char* msg, ...)
{
#if defined(ELEMENTARY_DEBUG)
	std::va_list args;
	va_start(args, msg);
	
#if defined(ELEMENTARY_WIN32)
	// TODO(fkp): Extract into a function
	// Gets colour info
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	WORD normalColour = info.wAttributes;

	// Colours "Error" in red
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
#endif

	std::fprintf(stderr, "Error: ");
	
#if defined(ELEMENTARY_WIN32)
	// Returns back to original colour
	SetConsoleTextAttribute(hConsole, normalColour);
#endif

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
	
	#if defined(ELEMENTARY_WIN32)
		// TODO(fkp): Extract into a function
		// Gets colour info
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(hConsole, &info);
		WORD normalColour = info.wAttributes;

		// Colours "Error" in red
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	#endif

		std::fprintf(stderr, "Error: ");
	
	#if defined(ELEMENTARY_WIN32)
		// Returns back to original colour
		SetConsoleTextAttribute(hConsole, normalColour);
	#endif

	std::vfprintf(stderr, msg, args);
	std::fprintf(stderr, "\nSDL_Error: %s\n", SDL_GetError());

	va_end(args);
#endif
}
