#pragma once

#include <random>

namespace el
{

class Random
{
private:
	// Random-number generator
	static std::mt19937 m_Rng;

public:
	static void init();

	// Gets a random integer in the range [min, max)
	static int randint(int min, int max);
	// Gets a random double in the range [min, max)
	static double randdouble(double min, double max);
};

}
