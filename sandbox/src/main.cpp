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

	std::unordered_map<std::string, std::string> defaultSettings = { { "TEXT", "Hello, World!" } };
	el::Settings settings = { defaultSettings };
	settings.setValue("TEXT", "Hello");
	el::Text text = { window.renderer, "res/arial.ttf", settings.getValue("TEXT"), 64};

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
		text.draw();
		SDL_RenderPresent(window.renderer);
	}

	settings.writeToFile();
	
	return 0;
}
