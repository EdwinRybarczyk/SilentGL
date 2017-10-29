#include "SilentMath.h"
#ifndef SILENT_RASTERIZER
#define SILENT_RASTERIZER
typedef struct Colour
{
	unsigned char r,g,b;
}Colour;

//vertex shader pointer
typedef void (*vsp)(vec3f* vert,);
//fragment shader pointer
typedef Colour (*fsp)(void*);

typedef enum SilentVboType
{
	SILENT_VAO_VEC4F,
	SILENT_VAO_VEC4I,
	SILENT_VAO_VEC3F,
	SILENT_VAO_VEC3I,
	SILENT_VAO_VEC2F,
	SILENT_VAO_VEC2I
}SilentVaoType;

typedef struct SilentVertexBuffer
{
	union
	{
		vec4f ** vector4f;
		vec4i ** vector4i;
		vec3f ** vector3f;
		vec3i ** vector3i;
		vec2f ** vector2f;
		vec2i ** vector2i;
	}
	SilentVboType vboType;
}SilentVertexBuffer;

typedef struct SilentVertexAttribute
{
	SilentVertexBuffer **vbo;

}SilentVertexAttribute;

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
	vsp vertexShader;
	fsp fragmentShader;
}SilentRasterizer;

SilentRasterizer* silentRasterizer;

void createSilentRasterizer(int screenWidth, int screenHeight);
void deleteSilentRasterizer();
SilentRasterizer* getSilentRasterizerRef();
char* silentGetRenderBuffer();

void silentLoadVertexCoordinates(vec3f** vertex, int vertexCount);
void silentLoadIndices(int* indices, int indiceCount);
void silentLoadVertexShader(vsp shader);
void silentLoadFragmentShader(fsp shader);
void silentApplyProjection(int fov, float near, float far);
void silentTranslate(float x, float y, float z);
void silentRenderIndices();
#endif
