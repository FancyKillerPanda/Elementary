#include <SDL/SDL.h>

#include "utils/log.h"
#include "gfx/texture.h"
#include "animations/scale.h"

namespace el
{

Scale::Scale(int durationMs, int newWidth, int newHeight, bool shouldStartImmediately, int waitDurationMs)
{
	init(durationMs, newWidth, newHeight, shouldStartImmediately, waitDurationMs);
}

Scale::Scale(Texture* p_Texture, int durationMs, int newWidth, int newHeight, bool shouldStartImmediately, int waitDurationMs)
{
	texture = p_Texture;
	init(durationMs, newWidth, newHeight, shouldStartImmediately, waitDurationMs);
}

void Scale::init(int durationMs, int newWidth, int newHeight, bool shouldStartImmediately, int waitDurationMs)
{
	type = Animation::Type::Scale;
	waitingDurationMs = waitDurationMs;

	startWidth = texture->rect.w;
	targetWidth = newWidth;
	startHeight = texture->rect.h;
	targetHeight = newHeight;

	targetDurationMs = durationMs;

	if (waitingDurationMs == 0 && shouldStartImmediately)
	{
		start();
	}
}

void Scale::start()
{
	if (!texture->texture)
	{
		warn("Cannot size change without valid texture.");
		return;
	}

	currentDurationMs = 0;
	timer.reset();

	texture->isScalingCurrently = true;
	hasStarted = true;
}

bool Scale::update()
{
	currentDurationMs = (int) timer.getElapsed();
	
	if (!waitIfNecessary())
	{
		return true;
	}

	if (currentDurationMs >= targetDurationMs)
	{
		// Makes sure the rect dimensions are exactly the target
		texture->rect.w = targetWidth;
		texture->rect.h = targetHeight;

		executeAfterAnimations();

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
