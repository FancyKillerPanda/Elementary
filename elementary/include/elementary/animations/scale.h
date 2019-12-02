#pragma once

#include "animations/animation.h"

namespace el
{

class Scale : public Animation
{
public:
	int startWidth = 0;
	int startHeight = 0;
	int targetWidth = 0;
	int targetHeight = 0;

public:
	Scale(int durationMs, int newWidth, int newHeight, bool shouldStartImmediately = false, int waitDurationMs = 0);
	Scale(Texture* texture, int durationMs, int newWidth, int newHeight, bool shouldStartImmediately = false, int waitDurationMs = 0);

	void start() override;
	bool update() override;

private:
	void init(int durationMs, int newWidth, int newHeight, bool shouldStartImmediately, int waitDurationMs);
};
	
}
