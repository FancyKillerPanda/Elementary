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
	Translate(int durationMs, int newX, int newY, bool shouldStartImmediately = true, int waitDurationMs = 0);
	Translate(Texture* p_Texture, int durationMs, int newX, int newY, bool shouldStartImmediately = true, int waitDurationMs = 0);

	void start() override;
	bool update() override;

private:
	void init(int durationMs, int newX, int newY, bool shouldStartImmediately, int waitDurationMs);
};
	
}
