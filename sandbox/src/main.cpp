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

	el::Menu menu = { texts, { 255, 255, 255, 255 }, { 0, 255, 0, 255 }, { 0, 64, 0, 255 }, { 0, 155, 0, 255 } };
	menu.setPositionsVertical(960 / 2, 540 / 2, 50);
	
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

			menu.handleEvent(window.event);
		}

		SDL_RenderClear(window.renderer);
		menu.draw();
		SDL_RenderPresent(window.renderer);
	}

	return 0;
}
