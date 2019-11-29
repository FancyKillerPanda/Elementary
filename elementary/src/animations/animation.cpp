#include "animations/animation.h"

namespace el
{

bool Animation::waitIfNecessary()
{
	if (waitingDurationMs != 0)
	{
		if (currentDurationMs >= waitingDurationMs)
		{
			// Has finished waiting
			timer.reset();
			currentDurationMs = (int) timer.getElapsed();

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
	
}
