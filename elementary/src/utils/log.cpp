#include <cstdio>
#include <cstdarg>
#include <atomic>
#include <mutex>

#if defined(ELEMENTARY_WIN32)
#include <windows.h>
#endif

#include <SDL/SDL.h>

#include "utils/log.h"
#include "utils/console_colour.h"

namespace el
{

// TODO(fkp): Maybe make these not global?
std::atomic<bool> shouldLockStdout;
std::mutex stdoutLockMutex;

void initLog(bool lockStdout)
{
	shouldLockStdout = lockStdout;
}

void info(const char* msg, ...)
{
#if defined(ELEMENTARY_DEBUG)
	std::va_list args;
	va_start(args, msg);

	if (shouldLockStdout.load()) stdoutLockMutex.lock();
	
	ConsoleColour::white();
	std::printf("Info: ");
	ConsoleColour::reset();
	std::vprintf(msg, args);
	std::printf("\n");

	if (shouldLockStdout.load()) stdoutLockMutex.unlock();

	va_end(args);
#endif
}

void warn(const char* msg, ...)
{
#if defined(ELEMENTARY_DEBUG)
	std::va_list args;
	va_start(args, msg);
	
	if (shouldLockStdout.load()) stdoutLockMutex.lock();
	
	ConsoleColour::yellow();
	std::printf("Warning: ");
	ConsoleColour::reset();
	std::vprintf(msg, args);
	std::printf("\n");

	if (shouldLockStdout.load()) stdoutLockMutex.unlock();
	
	va_end(args);
#endif
}

void error(const char* msg, ...)
{
#if defined(ELEMENTARY_DEBUG)
	std::va_list args;
	va_start(args, msg);

	if (shouldLockStdout.load()) stdoutLockMutex.lock();
	
	ConsoleColour::red();
	std::fprintf(stderr, "Error: ");
	ConsoleColour::reset();
	std::vfprintf(stderr, msg, args);
	std::fprintf(stderr, "\n");

	if (shouldLockStdout.load()) stdoutLockMutex.unlock();
	
	va_end(args);
#endif
}

void sdlError(const char* msg, ...)
{
#if defined(ELEMENTARY_DEBUG)
	std::va_list args;
	va_start(args, msg);

	if (shouldLockStdout.load()) stdoutLockMutex.lock();
	
	ConsoleColour::red();
	std::fprintf(stderr, "Error: ");
	ConsoleColour::reset();
	std::vfprintf(stderr, msg, args);
	std::fprintf(stderr, "\nSDL_Error: %s\n", SDL_GetError());

	if (shouldLockStdout.load()) stdoutLockMutex.unlock();
	
	va_end(args);
#endif
}

}
