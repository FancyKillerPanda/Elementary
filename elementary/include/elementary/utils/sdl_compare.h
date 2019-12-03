#include <SDL/SDL.h>

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
