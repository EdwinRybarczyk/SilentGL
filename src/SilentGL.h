#include "SilentMath.h"
#ifndef SILENT_RASTERIZER
#define SILENT_RASTERIZER
typedef struct SilentRasterizer
{
	char* pixels;
	int width,height;
	vec3f** vertices;
	int vertexCount;
	int* indices;
	int indiceCount;
	vec2f** textureCoords;
	int textureCoordCount;
}SilentRasterizer;

SilentRasterizer* silentRasterizer;

void createSilentRasterizer(int screenWidth, int screenHeight);
void deleteSilentRasterizer();
SilentRasterizer* getSilentRasterizerRef();
char* silentGetRenderBuffer();

void silentLoadVertexCoordinates(vec3f** vertex, int vertexCount);
void silentLoadIndices(int* indices, int indiceCount);
void silentApplyProjection(int fov, float near, float far);
void silentTranslate(float x, float y, float z);
void silentRenderIndices();
#endif
