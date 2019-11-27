#include <SDL/SDL.h>

#include <elementary.h>

int main(int argc, char* argv[])
{
	if (!el::init())
	{
		return -1;
	}
	
	el::Window window = { 960, 540, "Test Window" };
	bool running = window.isInitialised;

	std::vector<el::Text*> menuItems = {
		new el::Text(window.renderer, "res/arial.ttf", "One", 32),
		new el::Text(window.renderer, "res/arial.ttf", "Two", 32),
		new el::Text(window.renderer, "res/arial.ttf", "Three", 32),
	};
	el::Menu menu = { menuItems, SDL_Color { 255, 255, 255, 255 }, SDL_Color { 255, 0, 0, 255 }, SDL_Color { 127, 0, 0, 255 } };
	menu.setPositionsHorizontal(window.width / 2, window.height / 2, window.width / 6);

	el::Sound shootSound = { "res/Shoot Sound.mp3", 64 };
	el::Music backgroundMusic = { "res/Deep Space.mp3", 64 };
	backgroundMusic.play();

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

				case SDL_KEYDOWN:
				{
					if (window.event.key.keysym.sym == SDLK_SPACE)
					{
						backgroundMusic.togglePaused();
					}
				} break;
			}

			if (menu.handleEvent(window.event) == 0)
			{
				shootSound.play();
			}
		}

		SDL_RenderClear(window.renderer);
		menu.draw();
		SDL_RenderPresent(window.renderer);
	}
	
	return 0;
}
