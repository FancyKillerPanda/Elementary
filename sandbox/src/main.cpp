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
	el::Animation* fadeInAnimation = new el::Fade(&texture, 1000, 255, true);
	el::Animation* fadeOutAnimation = new el::Fade(&texture, 1000, 0);

	

	texture.animate(fadeInAnimation);
	texture.animate(fadeOutAnimation, fadeInAnimation);

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
