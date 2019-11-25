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

	el::InputText inputText = { window.renderer, "res/arial.ttf", "Blair" };
	inputText.currentText.setCenter(window.width / 2, window.height / 2);
	inputText.isSelected = true;

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

			inputText.handleEvent(window.event);
		}

		SDL_RenderClear(window.renderer);
		inputText.draw();
		SDL_RenderPresent(window.renderer);
	}
	
	return 0;
}
