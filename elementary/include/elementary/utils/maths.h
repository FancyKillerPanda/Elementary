#pragma once

#define ELEMENTARY_PI 3.14159265358979323846

namespace el
{

inline double toRadians(double value)
{
	return value * (ELEMENTARY_PI / 180);
}

inline double toDegrees(double value)
{
	return value * (180 / ELEMENTARY_PI);
}

}
