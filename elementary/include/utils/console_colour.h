#pragma once

#if defined(ELEMENTARY_WIN32)
#include <windows.h>
#endif

namespace el
{

class ConsoleColour
{
public:
	static bool isInitialised;

#if defined(ELEMENTARY_WIN32)
private:
	static HANDLE hConsole;
	static WORD defaultColour;
#endif

public:
	static void init();

	static void reset();
	static void red();
	static void green();
	static void blue();
	static void yellow();
	static void purple();
	static void cyan();
	static void white();
};

}
