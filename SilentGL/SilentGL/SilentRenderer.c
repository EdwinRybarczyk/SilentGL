#include "SilentRenderer.h"

SilentRenderer * silentCreateRenderer(SilentRasterizer * rasterizer)
{
	SilentRenderer* renderer = malloc(sizeof(SilentRasterizer));
	renderer->rasterizer = rasterizer;
	return renderer;
}

int silentConvertScreenCoordinateX(SilentScreen* screen, float coordinate) //
{
	int pixel = 0;
	pixel = (int)coordinate * screen->width;
	return pixel;
}

int silentConvertScreenCoordinateY(SilentScreen* screen, float coordinate)//
{
	int pixel = 0;
	pixel = (int)coordinate * screen->height;
	return pixel;
}

int silentConvertScreenCoordinateZ(SilentScreen* screen, float coordinate)//
{
	int pixel = 0;
	pixel = (int)coordinate * screen->height;
	return pixel;
}

void silentLoadVertex(
	SilentRenderer* renderer, Vertex3d* vertex, int vertexAmount)
{
}

void silentLoadRawVertex(
	SilentRenderer* renderer, Vertex3d* vertex, int vertexAmount)
{
	renderer->rasterizer->vertex = vertex;
	renderer->rasterizer->verticesArraySize = vertexAmount;
}

Vertex3d * silentCreateVertex(SilentScreen* screen, float * vertices, int arraySize)
{
	Vertex3d* vertex = calloc(arraySize, sizeof(Vertex3d));
	int vertpointer = 0;
	for (int i = 0; i < arraySize; i += 3) 
	{
		Vertex3d vert = *(Vertex3d*)malloc(sizeof(Vertex3d));
		vert.x = silentConvertScreenCoordinateX(screen, vertices[i]);
		vert.y = silentConvertScreenCoordinateY(screen, vertices[i+1]);
		vert.z = vertices[i+2];
		vertex[vertpointer++] = vert;
	}
	return vertex;
}

Vertex3d * silentCreateRawVertex(float * vertices, int arraySize)
{
	Vertex3d* vertex = calloc(arraySize, sizeof(Vertex3d));
	int vertpointer = 0;
	for (int i = 0; i < arraySize; i += 3)
	{
		Vertex3d vert = *(Vertex3d*)malloc(sizeof(Vertex3d));
		vert.x = vertices[i];
		vert.y = vertices[i + 1];
		vert.z = vertices[i + 2];
		vertex[vertpointer++] = vert;
	}
	return vertex;
}

void silentDrawTriangles(SilentRenderer * renderer)
{
}

void silentDrawTriangle(SilentRenderer * renderer)
{
	rasterizeTriangle(renderer->rasterizer);
}
