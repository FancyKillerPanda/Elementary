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

	std::vector<el::Text> texts;
	texts.push_back(el::Text { window.renderer, "res/arial.ttf", "Test", 32 });
	texts.push_back(el::Text { window.renderer, "res/arial.ttf", "Test1", 32 });
	texts.push_back(el::Text { window.renderer, "res/arial.ttf", "Test2", 32 });

	std::vector<el::Menu> menus;

	menus.emplace_back(texts, SDL_Color { 255, 255, 255, 255 }, SDL_Color { 0, 255, 0, 255 }, SDL_Color { 0, 64, 0, 255 }, SDL_Color { 0, 155, 0, 255 });
	menus.back().setPositionsVertical(960 * 3 / 5, 540 / 2, 50);
	menus.back().canUseUpDownKeys = false;

	menus.emplace_back(texts, SDL_Color { 255, 255, 255, 255 }, SDL_Color { 0, 255, 0, 255 }, SDL_Color { 0, 64, 0, 255 }, SDL_Color { 0, 155, 0, 255 });
	menus.back().setPositionsVertical(960 * 2 / 5, 540 / 2, 50);
	menus.back().canUseUpDownKeys = false;

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

			for (el::Menu& menu : menus)
			{
				menu.handleEvent(window.event);
			}
		}

		SDL_RenderClear(window.renderer);

		for (el::Menu& menu : menus)
		{
			menu.draw();
		}

		SDL_RenderPresent(window.renderer);
	}

	return 0;
}
