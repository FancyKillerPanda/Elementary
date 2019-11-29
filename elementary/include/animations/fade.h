#pragma once

#include "animations/animation.h"

namespace el
{

class Fade : public Animation
{
public:
	int startAlpha = 0;
	int targetAlpha = 0;

public:
	Fade(Texture* texture, int durationMs, unsigned char targetAlpha, int waitDurationMs = 0);

	void start() override;
	bool update() override;
};
	
}
