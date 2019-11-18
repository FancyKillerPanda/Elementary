#include <SDL/SDL.h>

#include <elementary.h>

void testLogging()
{
	el::error("No arguments!");
	el::error("One int: %d!", 10);
	el::error("One string and one int: %s and %d!", "Hello", 15);

	SDL_SetError("Example SDL2 error.");
	el::sdlError("Window creation failed.");

	el::warn("This is a warning.");
}

int main(int argc, char* argv[])
{
	testLogging();
	return 0;
}
