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

	el::Texture texture = { window.renderer, "res/basketball.png" };
	texture.fadeIn(1500, 1000);
	texture.smoothTranslate(1000, 500, 500, 2000);
	texture.smoothScale(1000, 2.0f, 3500);

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

		texture.update();

		SDL_RenderClear(window.renderer);
		texture.draw();
		SDL_RenderPresent(window.renderer);
	}
	
	return 0;
}
