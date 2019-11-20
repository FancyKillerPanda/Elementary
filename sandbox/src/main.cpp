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

	el::Menu oddMenu = { {
		new el::Text(window.renderer, "res/arial.ttf", "One", 32, SDL_Color { 255, 255, 255, 255 }),
		new el::Text(window.renderer, "res/arial.ttf", "Two", 32, SDL_Color { 255, 255, 255, 255 }),
		new el::Text(window.renderer, "res/arial.ttf", "Three", 32, SDL_Color { 255, 255, 255, 255 })
	}, SDL_Color { 255, 255, 255, 255 }, SDL_Color { 255, 255, 0, 255 }, SDL_Color { 160, 160, 0, 255 } };
	
	oddMenu.setCenter(window.width / 2, window.height / 2, window.width / 6);

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

			int oddMenuClickResult = oddMenu.handleEvent(window.event);

			if (oddMenuClickResult != -1)
			{
				el::info("Menu button %d clicked.", oddMenuClickResult);
			}
		}

		SDL_RenderClear(window.renderer);
		oddMenu.draw();
		SDL_RenderPresent(window.renderer);
	}
	
	return 0;
}
