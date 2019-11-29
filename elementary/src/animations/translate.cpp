#include <SDL/SDL.h>

#include "utils/log.h"
#include "gfx/texture.h"
#include "animations/translate.h"

namespace el
{

Translate::Translate(int durationMs, int newX, int newY, bool shouldStartImmediately, int waitDurationMs)
{
	init(durationMs, newX, newY, shouldStartImmediately, waitDurationMs);
}

Translate::Translate(Texture* p_Texture, int durationMs, int newX, int newY, bool shouldStartImmediately, int waitDurationMs)
{
	texture = p_Texture;
	init(durationMs, newX, newY, shouldStartImmediately, waitDurationMs);
}

void Translate::init(int durationMs, int newX, int newY, bool shouldStartImmediately, int waitDurationMs)
{
	type = Animation::Type::Translate;
	waitingDurationMs = waitDurationMs;

	startX = texture->rect.x;
	targetX = newX;
	startY = texture->rect.y;
	targetY = newY;

	targetDurationMs = durationMs;

	if (waitingDurationMs == 0 && shouldStartImmediately)
	{
		start();
	}
}

void Translate::start()
{
	if (!texture->texture)
	{
		warn("Cannot translate without valid texture.");
		return;
	}

	currentDurationMs = 0;
	timer.reset();

	texture->isTranslatingCurrently = true;
	hasStarted = true;
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

		executeAfterAnimations();

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
