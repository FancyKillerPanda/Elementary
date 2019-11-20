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

	el::Text buttonText = { window.renderer, "res/arial.ttf", "Button!", 32, SDL_Color { 255, 255, 255, 255 } };
	// Sets colour to white default, yellow on hover, and dark yellow on press
	buttonText.setColourValues(SDL_Color { 255, 255, 255, 255 }, SDL_Color { 255, 255, 0, 255 }, SDL_Color { 191, 191, 0, 255 });
	buttonText.setIsClickable(true);

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

			if (buttonText.handleEvent(window.event))
			{
				el::info("Button clicked.");
			}
		}

		SDL_RenderClear(window.renderer);
		buttonText.draw();
		SDL_RenderPresent(window.renderer);
	}
	
	return 0;
}
