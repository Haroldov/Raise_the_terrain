#include "sdl.h"

/**
 *main - Entry Point
 *Return: 0 always
 */

int main(void)
{
	SDL_Instance instance;

	if (init_instance(&instance) != 0)
		return (1);
	return (0);
}
