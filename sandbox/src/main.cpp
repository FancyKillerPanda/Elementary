#include <thread>

#include <SDL/SDL.h>

#include <elementary.h>

void doSomePrinting()
{
	el::info("This is information.");
	el::warn("This is a warning.");
	el::error("This is an error.");
}

int main(int argc, char* argv[])
{
	if (!el::init(true))
	{
		return -1;
	}

	el::Window window = { 960, 540, "Test Window" };
	bool running = window.isInitialised;

	std::thread t0(doSomePrinting);
	std::thread t1(doSomePrinting);
	t0.join();
	t1.join();
	
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
		SDL_RenderPresent(window.renderer);
	}

	return 0;
}
