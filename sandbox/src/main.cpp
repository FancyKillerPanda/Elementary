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
	texture.fadeOut(3000);
	texture.smoothTranslate(window.width - texture.rect.w, window.height - texture.rect.h, 3000);

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

		int animationsFinished = texture.update();

		if (animationsFinished & el::Animation::Fade)
		{
			el::info("Fade finished.");
		}
		if (animationsFinished & el::Animation::Scale)
		{
			el::info("Scale finished.");
		}

		if (animationsFinished & el::Animation::Translate)
		{
			el::info("Tanslate finished.");
		}

		SDL_RenderClear(window.renderer);
		texture.draw();
		SDL_RenderPresent(window.renderer);
	}
	
	return 0;
}
