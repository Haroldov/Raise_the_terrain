#include <stdio.h>
#include <math.h>
#include "sdl.h"

void draw_grid(SDL_Instance instance, float **z)
{
	extern unsigned int size;
	int res = size - 1;
	float inclination = 0.7;
	int width = SCREEN_WIDTH - SCREEN_WIDTH * 0.2;
	int height = SCREEN_HEIGHT - SCREEN_HEIGHT * 0.2;
	int x = 0, y = 0, dx = (width / res) - 1, dy = (height / res) - 1;
	int X = 0, Y = 0, Wx = 0, Wy = 0, xOffset = 270, yOffset = 200;
	int indx = 0, indy = 0;

	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	for (x = 0; x <= dx * res; x += dx)
	{
		indy = 0;
		for (y = 0; y < dy * res; y += dy)
		{
			X = (x * inclination) - (inclination * y) + xOffset;
			Y = y * (1 - inclination) + (1 - inclination) * x + yOffset - z[indx][indy];
			Wx = (x * inclination) - (inclination * (y + dy)) + xOffset;
			Wy = (1 - inclination) * x + (1 - inclination) * (y + dy) + yOffset - z[indx][indy + 1];
			SDL_RenderDrawLine(instance.renderer, X, Y, Wx, Wy);
			indy++;
		}
		indx++;
	}
 	indx = 0;
	indy = 0;
	for (y = 0; y <= dy * res; y += dy)
	{
		indx = 0;
		for (x = 0; x < dx * res; x += dx)
		{
			X = (x * inclination) - (inclination * y) + xOffset;
			Y = y * (1 - inclination) + x * (1 - inclination) + yOffset - z[indx][indy];
			Wx = (inclination * (x + dx)) - (inclination * y) + xOffset;
			Wy = (1 - inclination) * (x + dx) + (1 - inclination) * y + yOffset - z[indx + 1][indy];
			SDL_RenderDrawLine(instance.renderer, X, Y, Wx, Wy);
			indx++;
		}
		indy++;
	}
}

/**
 *MAIN - Entry Point
 *Return: 0 always
 */

int main(int argc, char *argv[])
{
	SDL_Instance instance;
	float **z = file2matrix(argv[1]);

	(void) argc;
	if (init_instance(&instance) != 0)
		return (1);
	while (1)
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);
		if (poll_events() == 1)
		 	break;
		draw_grid(instance, z);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	free_grid(z, 1);
	return (0);
}
