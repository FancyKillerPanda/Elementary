#pragma once

#include <SDL/SDL.h>

inline bool operator==(const SDL_Rect& first, const SDL_Rect& second)
{
	bool sameX = first.x == second.x;
	bool sameY = first.y == second.y;
	bool sameW = first.w == second.w;
	bool sameH = first.h == second.h;

	return sameX && sameY && sameW && sameH;
}

inline bool operator!=(const SDL_Rect& first, const SDL_Rect& second)
{
	return !(first == second);
}

inline bool operator==(const SDL_Color& first, const SDL_Color& second)
{
	bool sameR = first.r == second.r;
	bool sameG = first.g == second.g;
	bool sameB = first.b == second.b;
	bool sameA = first.a == second.a;

	return sameR && sameG && sameB && sameA;
}

inline bool operator!=(const SDL_Color& first, const SDL_Color& second)
{
	return !(first == second);
}
