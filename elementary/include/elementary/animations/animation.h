#pragma once

#include <vector>

#include "utils/timer.h"

namespace el
{

class Texture;

class Animation
{
public:
	enum class Type : char
	{
		None		= 0,		// 0000 == 0
		Fade		= 1 << 0,	// 0001 == 1
		Scale		= 1 << 1,	// 0010 == 2
		Translate	= 1 << 2,	// 0100 == 4
	};

public:
	Texture* texture;
	Timer timer;
	
	int currentDurationMs = 0;
	int targetDurationMs = 0;

	std::vector<Animation*> animationsToExecuteAfter;

protected:
	Type type;
	
	int waitingDurationMs = 0;
	bool hasStarted = false;

public:
	virtual ~Animation() {}

	// Returns false when the animation has finished
	virtual bool update() = 0;

protected:
	virtual void start() = 0;

	// Returns true if finished waiting
	bool waitIfNecessary();

	// Executes animations after this has finished
	void executeAfterAnimations();
};

}
