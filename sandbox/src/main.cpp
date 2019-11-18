#include <elementary.h>

void testLogging()
{
	error("No arguments!\n");
	error("One int: %d!\n", 10);
	error("One string and one int: %s and %d!\n", "Hello", 15);
}

int main()
{
	testLogging();
}
