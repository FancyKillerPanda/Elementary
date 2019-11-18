#include <SDL/SDL.h>

#include <elementary.h>

void testLogging()
{
	error("No arguments!");
	error("One int: %d!", 10);
	error("One string and one int: %s and %d!", "Hello", 15);

	SDL_SetError("Example SDL2 error.");
	sdlError("Window creation failed.");
}

int main(int argc, char* argv[])
{
	testLogging();
	return 0;
}
