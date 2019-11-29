#include <SDL/SDL.h>

#include "utils/log.h"
#include "gfx/texture.h"
#include "animations/fade.h"

namespace el
{

Fade::Fade(Texture* texture, int durationMs, unsigned char targetAlphaValue, int waitDurationMs)
	: Animation(texture)
{
	type = Type::Fade;
	waitingDurationMs = waitDurationMs;

	// Makes sure to start at at the opposite alpha value
	if (targetAlphaValue == 255 && startAlpha == 255)
	{
		startAlpha = 0;
	}
	else if (targetAlphaValue == 0 && startAlpha == 0)
	{
		startAlpha = 255;
	}

	targetAlpha = (int) targetAlphaValue;
	targetDurationMs = durationMs;

	if (waitingDurationMs == 0)
	{
		start();
	}
}

void Fade::start()
{
	if (!texture->texture)
	{
		warn("Cannot fade in without valid texture (filepath: %s).", texture->filepath.c_str());
		return;
	}

	SDL_SetTextureAlphaMod(texture->texture, (unsigned char) startAlpha);

	currentDurationMs = 0;
	timer.reset();

	texture->isFadingCurrently = true;
}

bool Fade::update()
{
	currentDurationMs = (int) timer.getElapsed();

	if (!waitIfNecessary())
	{
		return true;
	}

	if (currentDurationMs >= targetDurationMs)
	{
		// Makes sure the alpha is exactly the target
		SDL_SetTextureAlphaMod(texture->texture, (unsigned char) targetAlpha);
		return false;
	}

	double portionOfTimeCompleted = (double) currentDurationMs / (double) targetDurationMs;
	int fadeAlphaDifference = targetAlpha - startAlpha;
	unsigned char newAlpha = (unsigned char) (startAlpha + (fadeAlphaDifference * portionOfTimeCompleted));

	// Sets the new alpha of the texture
	SDL_SetTextureAlphaMod(texture->texture, newAlpha);

	return true;
}
	
}
