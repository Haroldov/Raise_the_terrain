#ifndef __SDL__
#define __SDL__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned int size;

/**
 *struct SDL_Instance - Instance of a SDL object.
 *@window: the SDL_Window pointer from the SDL object.
 *@renderer: the SDL_Renderer pointer from the SDL object.
 */

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *surface;
} SDL_Instance;

int init_instance(SDL_Instance *instance);
int poll_events(void);
float **file2matrix(char *filename);
float **alloc_grid(int width, int height);
unsigned int get_size(char *str, const char *delim);
void free_grid(float **grid, int height);

#endif

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 640
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 480
#endif
