#pragma once

#include <string>
#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "utils/timer.h"
#include "animations/fade.h"

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

	/*
	// Scale data
	int scaleStartWidth = 0;
	int scaleTargetWidth = 0;
	int scaleStartHeight = 0;
	int scaleTargetHeight = 0;
	int scaleCurrentDuration = 0;
	int scaleTargetDuration = 0;
	Timer scaleTimer;

	// Scale data
	int translateStartX = 0;
	int translateTargetX = 0;
	int translateStartY = 0;
	int translateTargetY = 0;
	int translateCurrentDuration = 0;
	int translateTargetDuration = 0;
	Timer translateTimer;
	*/

	std::vector<Animation*> animationsQueue;

public:
	Texture(SDL_Renderer* renderer);
	Texture(SDL_Renderer* renderer, std::string filepath);
	~Texture();

	void convertFromSurface(SDL_Surface* surfaceToConvertFrom);

	// Returns which animation(s) finished in that frame
	int update();
	void draw();

	// NOTE(fkp): Returns true if texture click state has changed
	bool handleEvent(const SDL_Event& event);

	// Fades the texture in over a duration of time
	void fadeIn(int durationMs);
	// Fades the texture out over a duration of time
	void fadeOut(int durationMs);

	// Scales the texture smoothly to a new width and height
	void smoothScale(int newWidth, int newHeight, int durationMs);
	// Scales the texture smoothly by a scale factor
	void smoothScale(double scaleFactor, int durationMs);

	// Moves the texture to a new location over a duration of time
	void smoothTranslate(int newX, int newY, int durationMs);

	void setTopLeft(int x, int y);
	void setCenter(int x, int y);
	void setRect(int x, int y, int width, int height);

	SDL_Point getCenter();
};

}
