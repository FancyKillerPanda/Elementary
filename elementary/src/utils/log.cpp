#include <cstdio>
#include <cstdarg>

#include "utils/log.h"

void error(const char* msg, ...)
{
	// TODO(fkp): Append newline
	std::va_list args;
	va_start(args, msg);
	std::vfprintf(stderr, msg, args);
	va_end(args);
}
