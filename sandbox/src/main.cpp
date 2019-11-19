#include <SDL/SDL.h>

#include <elementary.h>

int main(int argc, char* argv[])
{
	if (!el::initSDL())
	{
		return -1;
	}

	el::Window window = { 960, 540, "Test Window" };
	bool running = window.isInitialised;

	el::Texture basketballTexture = { window.renderer, "res/basketball.png" };

	while (running)
	{
		while (SDL_PollEvent(&window.event))
		{
			switch (window.event.type)
			{
				case SDL_QUIT:
				{
					running = false;
				} break;
			}
		}

		SDL_RenderClear(window.renderer);
		basketballTexture.draw();
		SDL_RenderPresent(window.renderer);
	}
	
	return 0;
}
