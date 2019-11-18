#include <elementary.h>

void testLogging()
{
	error("No arguments!");
	error("One int: %d!", 10);
	error("One string and one int: %s and %d!", "Hello", 15);
}

int main()
{
	testLogging();
}
