#pragma once

#include <stdio.h>

namespace el
{

void initLog(bool lockStdout);

void info(const char* msg, ...);
void warn(const char* msg, ...);
void error(const char* msg, ...);
void sdlError(const char* msg, ...);

}
