#include "StateManager.h"

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	StateManager stateManager;

	stateManager.run();

	return EXIT_SUCCESS;
}