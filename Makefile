output:
	gcc @flags *.c `sdl2-config --cflags` `sdl2-config --libs` -lm
