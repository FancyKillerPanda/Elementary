#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "utils/init.h"
#include "utils/log.h"
#include "utils/random.h"
#include "utils/console_colour.h"

namespace el
{

bool init(bool lockStdout)
{
	Random::init();
	ConsoleColour::init();
	initLog(lockStdout);
	
	return initSDL();
}

bool initSDL()
{
	// SDL2 init
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		sdlError("Failed to initialise SDL2.");
		return false;
	}

	// SDL2 image init
	int imgInitFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if ((IMG_Init(imgInitFlags) & imgInitFlags) != imgInitFlags)
	{
		sdlError("Failed to initialise SDL_image.");
		return false;
	}

	// SDL2 TTF init
	if (TTF_Init() != 0)
	{
		sdlError("Failed to initialise SDL_ttf.");
		return false;
	}

	// SDL2 mixer init
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
	{
		sdlError("Failed to open mixer audio.");
		return false;
	}

	return true;
}
	
}
