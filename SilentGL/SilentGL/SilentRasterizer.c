#include "SilentRasterizer.h"
#undef min
#undef max

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


float min(Vertex3d * vert) 
{
	float minval = vert->x;
	if (vert->y < vert->x) { minval = vert->y; }
	if ((vert->z < vert->y) || (vert->z < vert->x)) { minval = vert->z; }
	return minval;
}


float max(Vertex3d * vert)
{
	float maxval = vert->x;
	if (vert->y > vert->x) { maxval = vert->y; }
	if ((vert->z > vert->y) || (vert->z > vert->x)) { maxval = vert->z; }
	return maxval;
}


void rasterizeTriangle(SilentRasterizer* rasterizer)
{
	//calculate bounding box
	int minx = min(rasterizer->vertex + 0);
	int maxx = max(rasterizer->vertex + 0);
	int miny = min(rasterizer->vertex + 0);
	int maxy = max(rasterizer->vertex + 0);

	for (int y = miny; y < maxy; y++) 
	{
		for (int x = minx; x < maxx; x++)
		{
			setPixel(
				rasterizer->screen->pixels,
				x + y * rasterizer->screen->width,
				255, 0, 0, 255
			);
		}
	}
}