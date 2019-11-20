#pragma once

#include <stdio.h>

namespace el
{

void info(const char* msg, ...);
void warn(const char* msg, ...);
void error(const char* msg, ...);
void sdlError(const char* msg, ...);

}
