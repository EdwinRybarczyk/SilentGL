#include "SilentRasterizer.h"

SilentRasterizer * createSilentRasterizer(SilentScreen * screen)
{
	SilentRasterizer* rasterizer = malloc(sizeof(SilentRasterizer));
	rasterizer->screen = screen;
	return rasterizer;
}

void deleteSilentRasterizer(SilentRasterizer * rasterizer)
{
	free(rasterizer);
}

void rasterizeTriangle(SilentRasterizer* rasterizer)
{
}
