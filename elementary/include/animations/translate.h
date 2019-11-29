#pragma once

#include "animations/animation.h"

namespace el
{

class Translate : public Animation
{
public:
	int startX = 0;
	int startY = 0;
	int targetX = 0;
	int targetY = 0;

public:
	Translate(Texture* texture, int durationMs, int newX, int newY, int waitDurationMs = 0);

	void start() override;
	bool update() override;
};
	
}
