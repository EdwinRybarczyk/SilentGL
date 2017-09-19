#pragma once
#include "SilentScreen.h"
typedef struct Vertex3d 
{
	float x;
	float y;
	float z;
}Vertex3d;

typedef struct SilentRasterizer 
{
	Vertex3d* vertex;
	int verticesArraySize;
	SilentScreen* screen;

}SilentRasterizer;

SilentRasterizer* createSilentRasterizer(SilentScreen* screen);
void deleteSilentRasterizer(SilentRasterizer* rasterizer);
void rasterizeTriangle(SilentRasterizer* rasterizer);
