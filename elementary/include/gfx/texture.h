#pragma once

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "utils/timer.h"

namespace el
{

enum class TextureClickState
{
	None,		// Mouse not over the texture
	Hover,		// On mouse over
	Pressed,	// On mouse down
	Clicked		// On mouse up
};

class Texture
{
public:
	bool isInitialised = false;
	SDL_Renderer* renderer;

	std::string filepath;
	SDL_Texture* texture = nullptr;
	SDL_Rect rect = {};

	bool isClickable = false;
	TextureClickState currentClickState = TextureClickState::None;

	// Fade data
	bool currentlyFading = false;
	int startFadeAlpha = 0;
	int targetFadeAlpha = 0;
	int currentFadeDuration = 0;
	int targetFadeDuration = 0;
	Timer fadeTimer;

	// Size change data
	bool currentlyChangingSize = false;
	int startWidth = 0;
	int targetWidth = 0;
	int startHeight = 0;
	int targetHeight = 0;
	int currentSizeChangeDuration = 0;
	int targetSizeChangeDuration = 0;
	Timer sizeChangeTimer;

private:
	TextureClickState lastClickState = TextureClickState::None;

public:
	Texture(SDL_Renderer* renderer);
	Texture(SDL_Renderer* renderer, std::string filepath);
	~Texture();

	void convertFromSurface(SDL_Surface* surfaceToConvertFrom);

	void update();
	void draw();

	// NOTE(fkp): Returns true if texture click state has changed
	bool handleEvent(const SDL_Event& event);

	// Fades the texture in over a duration of time
	void fadeIn(int durationMs);
	// Fades the texture out over a duration of time
	void fadeOut(int durationMs);

	// Changes the size of the texture smoothly
	void smoothSizeChange(int newWidth, int newHeight, int durationMs);

	void setTopLeft(int x, int y);
	void setCenter(int x, int y);
	void setRect(int x, int y, int width, int height);

	SDL_Point getCenter();
};

}
