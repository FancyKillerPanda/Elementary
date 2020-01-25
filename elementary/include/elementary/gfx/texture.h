#pragma once

#include <string>
#include <vector>
#include <unordered_map>

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
	SDL_Renderer* renderer = nullptr;

	std::string filepath;
	SDL_Texture* texture = nullptr;
	SDL_Rect rect = {};

	double rotation = 0; // Measured from the positive x-axis; see unit circle

	bool isClickable = false;
	TextureClickState currentClickState = TextureClickState::None;

	bool isFadingCurrently = false;
	bool isScalingCurrently = false;
	bool isTranslatingCurrently = false;

private:
	static std::unordered_map<SDL_Texture*, unsigned int> s_TextureCountMap;
	TextureClickState lastClickState = TextureClickState::None;

	std::vector<Animation*> animationsRunning;
	SDL_Rect textureSubRect = {};

public:
	Texture() = default;
	Texture(SDL_Renderer* renderer, std::string filepath);
	Texture(const Texture& from);
	Texture& operator=(Texture from);
	Texture(Texture&& from);
	~Texture();

	void convertFromSurface(SDL_Renderer* p_Renderer, SDL_Surface* surfaceToConvertFrom);
	friend void swap(Texture& first, Texture& second);
	void destroyTexture();
	
	// Returns whether an animation has finished
	bool update();
	void draw();

	// NOTE(fkp): Returns true if texture click state has changed
	bool handleEvent(const SDL_Event& event);

	// Executes an animation in
	void animate(Animation* animation);
	// Executes an animation after another animation
	void animate(Animation* animationToDo, Animation* executeAfter);

	// Fades the texture in over a duration of time
	void fadeIn(int durationMs, int waitDurationMs = 0);
	// Fades the texture out over a duration of time
	void fadeOut(int durationMs, int waitDurationMs = 0);

	// Scales the texture smoothly to a new width and height
	void smoothScale(int durationMs, int newWidth, int newHeight, int waitDurationMs = 0);
	// Scales the texture smoothly by a scale factor
	void smoothScale(int durationMs, double scaleFactor, int waitDurationMs = 0);

	// Moves the texture to a new location over a duration of time
	void smoothTranslate(int durationMs, int newX, int newY, int waitDurationMs = 0);

	// Sets the texture to use a different portion
	void setSubRect(int x, int y, int width, int height);
	void setSubRect(SDL_Rect rect);

	void setTopLeft(int x, int y);
	void setCenter(int x, int y);
	void setRect(int x, int y, int width, int height);

	SDL_Point getCenter() const;

private:
	bool handleTextureCreationChecks();
};

}
