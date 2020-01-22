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
	texts.push_back(el::Text { window.renderer, "res/arial.ttf", "Test", 64 });

	el::Text myText;
	myText = el::Text { window.renderer, "res/arial.ttf", "Test1", 64 };
	myText.setTopLeft(100, 100);

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

		for (el::Text& text : texts)
		{
			text.draw();
		}

		myText.draw();

		SDL_RenderPresent(window.renderer);
	}

	return 0;
}
