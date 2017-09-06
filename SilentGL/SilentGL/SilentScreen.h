#pragma once
#include <stdlib.h>
typedef struct SilentScreen 
{
	char* pixels;
	float* depthBuffer;
	unsigned int width;
	unsigned int height;

}SilentScreen;

SilentScreen* createSilentScreen(int width, int height);
void deleteSilentScreen(SilentScreen* screen);
void setPixel(char *pixels, int pixel, char r, char g, char b, char a);