#include "sdl.h"

int init_instance(SDL_Instance *instance)
{
	/*Initialize SDL*/
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	/*Create a new Window Instance*/
	instance->window = SDL_CreateWindow("SDL2 - LEARNING GRAPHIC PROGRAMMING IN C",
					    SDL_WINDOWPOS_CENTERED,
					    SDL_WINDOWPOS_CENTERED,
					    SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/*Crete a new Renderer instance linked to the Window*/
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
						SDL_RENDERER_ACCELERATED |
						SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	return (0);

}


int poll_events(void)
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			key = event.key;
			if (key.keysym.scancode == 0x29)
				return (1);
			break;
		}
	}
	return (0);
}

float **file2matrix(char *filename)
{
	FILE *fileDesc = NULL;
	char *buffer = NULL, *num;
	size_t numBytes = 0;
	int sw = 0;
	unsigned int size = 0, i = 0, j = 0;
	float **grid = NULL;

	if (filename == NULL)
		return (0);
	fileDesc = fopen(filename, "r");
	while (getline(&buffer, &numBytes, fileDesc) != -1)
	{
		j = 0;
		if (sw == 0)
		{
			size = get_size(buffer, " \n");
			grid = alloc_grid(size, size);
			sw = 1;
		}
		num = strtok(buffer, " \n");
		while (num != NULL)
		{
			grid[j][i] = strtof(num, NULL);
			num = strtok(NULL, " \n");
			j++;
		}
		free(buffer);
		buffer = NULL;
		i++;
	}
	return (grid);
}

/**
 *alloc_grid - creates a 2 dimensional array of floats
 *@width: width of the array
 *@height: height of the array
 *Return: a pointer to a 2 dimensional array of floats
 */

float **alloc_grid(int width, int height)
{
	float *tmp;
	float **arr;
	int i;
	int size = width * height;

	if (width <= 0 || height <= 0 || size <= 0)
		return (NULL);

	arr =  malloc(height * sizeof(float *));
	tmp =  malloc(size * sizeof(float));

	if (arr == NULL || tmp == NULL)
	{
		free(tmp);
		free(arr);
		return (NULL);
	}


	for (i = 0; i < height; i++)
		arr[i] = tmp + (i * width);

	for (i = 0; i < size; i++)
		tmp[i] = 0;

	return (arr);
}

/**
 *split - splits a string according to the delimiter
 *@str: pointer to the string
 *@delim: pointer to the delimiter
 *Return: a number
 */
unsigned int size;

unsigned int get_size(char *str, const char *delim)
{
	char *buffer, *tmpCpy = strdup(str);
	unsigned int wNum = 0;

	if (*str == '\0')
	{
		free(tmpCpy);
		return (-1);
	}
	/*Count the number of words to allocate memory*/
	buffer = strtok(tmpCpy, delim);
	wNum += 1;
	while (buffer != NULL)
	{
		buffer = strtok(NULL, delim);
		if (buffer != NULL)
			wNum += 1;
	}
	free(tmpCpy);
	size = wNum;
	return (wNum);
}

/**
 *free_grid - free a grid
 *@grid: grid to be released
 *@height: height of the grid
 *Return: none
 */

void free_grid(float **grid, int height)
{
	if (grid == NULL || height == 0)
	{
	}
	else
	{
		free(grid[0]);
		free(grid);
	}
}
