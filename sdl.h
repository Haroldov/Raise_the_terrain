#ifndef __SDL__
#define __SDL__

#include <SDL2/SDL.h>

/**
 *struct SDL_Instance - Instance of a SDL object.
 *@window: the SDL_Window pointer from the SDL object.
 *@renderer: the SDL_Renderer pointer from the SDL object.
 */

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *);

#endif
