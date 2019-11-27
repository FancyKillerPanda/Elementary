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

	el::Texture texture0 = { window.renderer, "res/basketball.png" };
	el::Texture texture1 = { window.renderer, "res/basketball.png" };
	texture1.setTopLeft(texture0.rect.w, 0);
	texture0.fadeOut(1000);
	texture1.fadeIn(1000);

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
						texture0.fadeIn(1000);
					}
				} break;
			}
		}

		texture0.update();
		texture1.update();

		SDL_RenderClear(window.renderer);
		texture0.draw();
		texture1.draw();
		SDL_RenderPresent(window.renderer);
	}
	
	return 0;
}
