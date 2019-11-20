#include "utils/console_colour.h"

namespace el
{

bool ConsoleColour::isInitialised = false;
#if defined(ELEMENTARY_WIN32)
HANDLE ConsoleColour::hConsole = nullptr;
WORD ConsoleColour::defaultColour = 0;
#endif

void ConsoleColour::init()
{
#if defined(ELEMENTARY_WIN32)
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	defaultColour = info.wAttributes;
#endif

	isInitialised = true;
}

void ConsoleColour::reset()
{
	if (!isInitialised)
	{
		return;
	}
	
#if defined(ELEMENTARY_WIN32)
	SetConsoleTextAttribute(hConsole, defaultColour);
#endif
}

void ConsoleColour::red()
{
	if (!isInitialised)
	{
		return;
	}
	
#if defined(ELEMENTARY_WIN32)
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
#endif
}

void ConsoleColour::green()
{
	if (!isInitialised)
	{
		return;
	}
	
#if defined(ELEMENTARY_WIN32)
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#endif
}

void ConsoleColour::blue()
{
	if (!isInitialised)
	{
		return;
	}
	
#if defined(ELEMENTARY_WIN32)
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#endif
}

void ConsoleColour::yellow()
{
	if (!isInitialised)
	{
		return;
	}
	
#if defined(ELEMENTARY_WIN32)
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#endif
}

void ConsoleColour::purple()
{
	if (!isInitialised)
	{
		return;
	}
	
#if defined(ELEMENTARY_WIN32)
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#endif
}

void ConsoleColour::cyan()
{
	if (!isInitialised)
	{
		return;
	}
	
#if defined(ELEMENTARY_WIN32)
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#endif
}

void ConsoleColour::white()
{
	if (!isInitialised)
	{
		return;
	}
	
#if defined(ELEMENTARY_WIN32)
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#endif
}

}
