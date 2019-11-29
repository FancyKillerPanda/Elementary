#include <SDL/SDL.h>

#include "utils/log.h"
#include "gfx/texture.h"
#include "animations/scale.h"

namespace el
{

Scale::Scale(Texture* texture, int durationMs, int newWidth, int newHeight)
	: Animation(texture)
{
	if (!texture->texture)
	{
		warn("Cannot size change without valid texture.");
		return;
	}

	texture->isScalingCurrently = true;

	startWidth = texture->rect.w;
	targetWidth = newWidth;
	startHeight = texture->rect.h;
	targetHeight = newHeight;

	currentDurationMs = 0;
	targetDurationMs = durationMs;
	timer.reset();
}

bool Scale::update()
{
	currentDurationMs = (int) timer.getElapsed();

	if (currentDurationMs >= targetDurationMs)
	{
		// Makes sure the rect dimensions are exactly the target
		texture->rect.w = targetWidth;
		texture->rect.h = targetHeight;

		return false;
	}

	double portionOfTimeCompleted = (double) currentDurationMs / (double) targetDurationMs;
		
	int widthDifference = targetWidth - startWidth;
	texture->rect.w = (int) (startWidth + (widthDifference * portionOfTimeCompleted));
	int heightDifference = targetHeight - startHeight;
	texture->rect.h = (int) (startHeight + (heightDifference * portionOfTimeCompleted));

	return true;
}
	
}
