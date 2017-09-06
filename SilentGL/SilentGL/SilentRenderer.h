#pragma once
#include "SilentRasterizer.h"
typedef struct SilentRenderer {
	SilentRasterizer* rasterizer;
}SilentRenderer;

SilentRenderer* silentCreateRenderer(SilentRasterizer* rasterizer);
void silentLoadVertex(
	SilentRenderer* renderer, Vertex3d* vertex, int vertexAmount);
void silentLoadRawVertex(
	SilentRenderer* renderer, Vertex3d* vertex, int vertexAmount);
Vertex3d* silentCreateVertex(float* vertices, int arraySize);
Vertex3d* silentCreateRawVertex(float* vertices, int arraySize);
void silentDrawTriangles(SilentRenderer* renderer);
void silentDrawTriangle(SilentRenderer* renderer);