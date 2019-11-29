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
	texture.smoothTranslate(1000, 500, 500);
	texture.smoothScale(500, 2.0f);

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
