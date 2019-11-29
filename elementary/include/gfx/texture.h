#pragma once

#include <string>
#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "utils/timer.h"
#include "animations/animation.h"

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

	bool isFadingCurrently = false;
	bool isScalingCurrently = false;
	bool isTranslatingCurrently = false;

private:
	TextureClickState lastClickState = TextureClickState::None;
	
	std::vector<Animation*> animationsQueue;

public:
	Texture(SDL_Renderer* renderer);
	Texture(SDL_Renderer* renderer, std::string filepath);
	~Texture();

	void convertFromSurface(SDL_Surface* surfaceToConvertFrom);

	// Returns whether an animation has finished
	bool update();
	void draw();

	// NOTE(fkp): Returns true if texture click state has changed
	bool handleEvent(const SDL_Event& event);

	// Fades the texture in over a duration of time
	void fadeIn(int durationMs);
	// Fades the texture out over a duration of time
	void fadeOut(int durationMs);

	// Scales the texture smoothly to a new width and height
	void smoothScale(int durationMs, int newWidth, int newHeight);
	// Scales the texture smoothly by a scale factor
	void smoothScale(int durationMs, double scaleFactor);

	// Moves the texture to a new location over a duration of time
	void smoothTranslate(int durationMs, int newX, int newY);

	void setTopLeft(int x, int y);
	void setCenter(int x, int y);
	void setRect(int x, int y, int width, int height);

	SDL_Point getCenter();
};

}
