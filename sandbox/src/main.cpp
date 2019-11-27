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
	SDL_SetTextureAlphaMod(texture.texture, 100);
	texture.fadeOut(500);

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
