#include <SDL/SDL.h>

#include <elementary.h>

int main(int argc, char* argv[])
{
	if (!el::initSDL())
	{
		return -1;
	}

	el::Window window = { 960, 540, "Test Window" };
	bool running = window.isInitialised;

	el::Texture basketballTexture = { window.renderer, "res/basketball.png" };
	el::Text helloText = { window.renderer, "res/arial.ttf", "Hello, there!", 48, SDL_Color { 255, 255, 255, 255 } };
	helloText.setPosition(100, 100);

	printf("X: %d\n", helloText.texture.rect.x);
	printf("Y: %d\n", helloText.texture.rect.y);
	printf("W: %d\n", helloText.texture.rect.w);
	printf("H: %d\n", helloText.texture.rect.h);


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
		basketballTexture.draw();
		helloText.draw();
		SDL_RenderPresent(window.renderer);
	}
	
	return 0;
}
