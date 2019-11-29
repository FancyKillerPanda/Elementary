#include <SDL/SDL.h>

#include "utils/log.h"
#include "gfx/texture.h"
#include "animations/translate.h"

namespace el
{

Translate::Translate(Texture* texture, int durationMs, int newX, int newY, int waitDurationMs)
	: Animation(texture)
{
	type = Animation::Type::Translate;
	waitingDurationMs = waitDurationMs;

	if (!texture->texture)
	{
		warn("Cannot translate without valid texture.");
		return;
	}

	texture->isTranslatingCurrently = true;

	startX = texture->rect.x;
	targetX = newX;
	startY = texture->rect.y;
	targetY = newY;

	currentDurationMs = 0;
	targetDurationMs = durationMs;
	timer.reset();
}

bool Translate::update()
{
	currentDurationMs = (int) timer.getElapsed();

	if (!waitIfNecessary())
	{
		return true;
	}

	if (currentDurationMs >= targetDurationMs)
	{
		// Makes sure the rect positions are exactly the target
		texture->rect.x = targetX;
		texture->rect.y = targetY;

		return false;
	}

	double portionOfTimeCompleted = (double) currentDurationMs/ (double) targetDurationMs;
		
	int xDifference = targetX - startX;
	int yDifference = targetY - startY;
	texture->rect.x = (int) (startX + (xDifference * portionOfTimeCompleted));
	texture->rect.y = (int) (startY + (yDifference * portionOfTimeCompleted));

	return true;
}

}
