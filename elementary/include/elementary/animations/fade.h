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
	Fade(int durationMs, unsigned char targetAlphaValue, bool shouldStartImmediately = false, int waitDurationMs = 0);
	Fade(Texture* p_Texture, int durationMs, unsigned char targetAlphaValue, bool shouldStartImmediately = false, int waitDurationMs = 0);

	void start() override;
	bool update() override;

private:
	void init(int durationMs, unsigned char targetAlpha, bool shouldStartImmediately, int waitDurationMs);
};
	
}
