#pragma once
#include "SilentScreen.h"
typedef struct SilentRasterizer 
{
	Vertex3d* vertex;
	int verticesArraySize;
	SilentScreen* screen;
}SilentRasterizer;

SilentRasterizer* createSilentRasterizer(SilentScreen* screen);
void deleteSilentRasterizer(SilentRasterizer* rasterizer);
void rasterizeTriangle(SilentRasterizer* rasterizer);

typedef struct Vertex3d 
{
	float x, y, z;
}Vertex3d;