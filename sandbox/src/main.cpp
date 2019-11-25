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

	el::InputText inputText = { window.renderer, "res/arial.ttf", "Hello" };
	inputText.setCenter(window.width / 2, window.height / 2);
	inputText.selectedColour = SDL_Colour { 255, 0, 0, 255 };
	inputText.setIsSelected(true);

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
					// Test: toggles text selection
					if (window.event.key.keysym.sym == SDLK_ESCAPE)
					{
						inputText.setIsSelected(!inputText.getIsSelected());
					}
					else if (window.event.key.keysym.sym == SDLK_RETURN)
					{
						el::info("%s", inputText.text.c_str());
					}
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
