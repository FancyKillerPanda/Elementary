#include <SDL/SDL.h>

#include "utils/log.h"
#include "gfx/texture.h"
#include "animations/fade.h"

namespace el
{

Fade::Fade(Texture* texture, int durationMs, unsigned char targetAlphaValue)
	: Animation(texture)
{
	type = Type::Fade;

	if (SDL_GetTextureAlphaMod(texture->texture, (Uint8*) &startAlpha) == -1)
	{
		warn("Cannot fade in without valid texture (filepath: %s).", texture->filepath.c_str());
		return;
	}

	texture->isFadingCurrently = true;

	// Makes sure to start at at the opposite alpha value
	if (targetAlphaValue == 255 && startAlpha == 255)
	{
		startAlpha = 0;
		SDL_SetTextureAlphaMod(texture->texture, (unsigned char) startAlpha);
	}
	else if (targetAlphaValue == 0 && startAlpha == 0)
	{
		startAlpha = 255;
		SDL_SetTextureAlphaMod(texture->texture, (unsigned char) startAlpha);
	}

	targetAlpha = (int) targetAlphaValue;

	currentDurationMs = 0;
	targetDurationMs = durationMs;
	timer.reset();
}

bool Fade::update()
{
	currentDurationMs = (int) timer.getElapsed();

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
