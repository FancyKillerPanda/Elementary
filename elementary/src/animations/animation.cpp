#include "animations/animation.h"

namespace el
{

bool Animation::waitIfNecessary()
{
	if (!hasStarted)
	{
		return false;
	}
	
	if (waitingDurationMs != 0)
	{
		if (currentDurationMs >= waitingDurationMs)
		{
			// Has just finished waiting
			start();
			waitingDurationMs = 0;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

void Animation::executeAfterAnimations()
{
	for (Animation* animation : animationsToExecuteAfter)
	{
		animation->start();
	}

	animationsToExecuteAfter.clear();
}
	
}
