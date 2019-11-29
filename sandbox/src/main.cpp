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
	el::Texture texture1 = { window.renderer, "res/basketball.png" };
	texture1.setTopLeft(texture.rect.w, 0);
	texture.fadeOut(1000);
	texture1.fadeIn(500);

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
		texture1.update();

		SDL_RenderClear(window.renderer);
		texture.draw();
		texture1.draw();
		SDL_RenderPresent(window.renderer);
	}
	
	return 0;
}
