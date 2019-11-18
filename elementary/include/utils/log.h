#pragma once

#include <stdio.h>

namespace el
{

void warn(const char* msg, ...);
void error(const char* msg, ...);
void sdlError(const char* msg, ...);

}
