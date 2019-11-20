#include <SDL/SDL.h>

#include <elementary.h>

int main(int argc, char* argv[])
{
	if (!el::init())
	{
		return -1;
	}
	
	el::info("%d | %f", el::Random::randint(0, 10), el::Random::randdouble(0.0, 10.0));

	el::Window window = { 960, 540, "Test Window" };
	bool running = window.isInitialised;

	el::Menu menu = { {
		new el::Text(window.renderer, "res/arial.ttf", "One", 32),
		new el::Text(window.renderer, "res/arial.ttf", "Two", 32),
		new el::Text(window.renderer, "res/arial.ttf", "Three", 32),
		new el::Text(window.renderer, "res/arial.ttf", "Four", 32)
	}, SDL_Color { 255, 255, 255, 255 }, SDL_Color { 255, 255, 0, 255 }, SDL_Color { 160, 160, 0, 255 } };

	menu.setPositionsHorizontal(window.width / 2, window.height / 2, window.width / 6);
	// menu.setPositionsVertical(window.width / 2, window.height / 2, window.height / 6);

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

			int oddMenuClickResult = menu.handleEvent(window.event);

			if (oddMenuClickResult != -1)
			{
				el::info("Menu button %d clicked.", oddMenuClickResult);
			}
		}

		SDL_RenderClear(window.renderer);
		menu.draw();
		SDL_RenderPresent(window.renderer);
	}
	
	return 0;
}
