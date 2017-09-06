#include "SilentScreen.h"
SilentScreen* createSilentScreen(int width, int height) 
{
	SilentScreen* screen = malloc(sizeof(SilentScreen));
	screen->width = width;
	screen->height = height;
	screen->pixels = calloc(width * height * 4, 1);
	screen->depthBuffer = calloc(width, height, 4);
	return screen;
}

void deleteSilentScreen(SilentScreen * screen)
{
	free(screen);
}

void setPixel(char * pixels, int pixel, char r, char g, char b, char a)
{
	pixel *= 4;
	pixels[pixel] = a;
	pixels[pixel + 1] = b;
	pixels[pixel + 2] = g;
	pixels[pixel + 3] = r;
}
