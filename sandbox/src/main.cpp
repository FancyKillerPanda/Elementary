#include <SDL/SDL.h>

#include <elementary.h>

struct TestStruct
{
	el::Text text;
};

int main(int argc, char* argv[])
{
	if (!el::init())
	{
		return -1;
	}
	
	el::Window window = { 960, 540, "Test Window" };
	bool running = window.isInitialised;

	std::vector<el::Text> texts;
	texts.push_back(el::Text { window.renderer, "res/arial.ttf", "Test", 64 });

	TestStruct testStruct = {};
	testStruct.text = el::Text { window.renderer, "res/arial.ttf", "Miss Scarlett's Turn!", 32 };
	testStruct.text.setTopLeft(100, 100);

	printf("%d, %d\n", testStruct.text.texture.rect.w, testStruct.text.texture.rect.h);
	
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

		for (el::Text& text : texts)
		{
			text.draw();
		}

		testStruct.text.draw();

		SDL_RenderPresent(window.renderer);
	}

	return 0;
}
