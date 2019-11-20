#pragma once

#include <chrono>

namespace el
{

class Timer
{
	// Avoids having to type out long name
	using Clock = std::chrono::high_resolution_clock;

private:
	// Start time or time of last reset
	Clock::time_point m_Start;

public:
	Timer()
	{
		reset();
	}

	inline void reset()
	{
		m_Start = Clock::now();
	}

	inline double getElapsed()
	{
		std::chrono::duration<double, std::milli> diff = Clock::now() - m_Start;
		return diff.count();
	}
};

}
