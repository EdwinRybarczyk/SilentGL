#include "SilentMath.h"
#ifndef SILENT_RASTERIZER
#define SILENT_RASTERIZER
//Colour in red, green, blue format
typedef struct Colour
{
	unsigned char r,g,b;
}Colour;

//Type of vertex buffer object
typedef enum SilentVboType
{
	SILENT_VBO_VEC4F,
	SILENT_VBO_VEC4I,
	SILENT_VBO_VEC3F,
	SILENT_VBO_VEC3I,
	SILENT_VBO_VEC2F,
	SILENT_VBO_VEC2I,
	SILENT_VBO_VERTEX,
	SILENT_VBO_INDICE
}SilentVboType;

//Vertex buffer
typedef struct SilentVertexBuffer
{
	union
	{
		vec4f *vector4f;
		vec4i *vector4i;
		vec3f *vector3f;
		vec3i *vector3i;
		vec2f *vector2f;
		vec2i *vector2i;
		int* integer;
	};
	//Type of the vertex buffer
	SilentVboType vboType;
	//Size of the vertex buffer
	long vboCount;
	//Iterator for the buffer
	long vboCounter;
}SilentVertexBuffer;

//Vertex array
typedef struct SilentVertexArray
{	
	//Array of VBOs
	SilentVertexBuffer *vbo;
	//Number of VBOs
	int vboCount;
}SilentVertexArray;

//vertex shader pointer
typedef void (*vsp)();
//fragment shader pointer
typedef Colour (*fsp)();

//Rasterization manager
typedef struct SilentRasterizer
{
	//Drawing buffer
	char* pixels;
	//Size of the screen in pixels
	int width,height;
	//Vertex Attributes
	SilentVertexArray *vao;
	//Vertex shader
	vsp vertexShader;
	//Fragment shader
	fsp fragmentShader;
}SilentRasterizer;

//Global rasterizer
SilentRasterizer* silentRasterizer;

//Create rasterizer
void createSilentRasterizer(int screenWidth, int screenHeight);
//Delete rasterizer
void deleteSilentRasterizer();
//Return pointer to the rasterizer
SilentRasterizer* getSilentRasterizerRef();
//Return pointer to drawing buffer
char* silentGetRenderBuffer();
/*
void silentLoadVertexCoordinates(vec3f** vertex, int vertexCount);
void silentLoadIndices(int* indices, int indiceCount);
*/
//Create a new VAO
SilentVertexArray* silentCreateVao(int size);
//Load a new VAO
void silentLoadVao(SilentVertexArray* vao);
//Create a new VBO
SilentVertexBuffer* silentCreateVbo(SilentVboType type,long size);
//Load a new VBO to a VAO
void silentLoadVbo(SilentVertexArray* vao,SilentVertexBuffer* vbo);
//Load the vertex shader
void silentLoadVertexShader(vsp shader);
//Load the fragment shader
void silentLoadFragmentShader(fsp shader);
//void silentApplyProjection(int fov, float near, float far);
//void silentTranslate(float x, float y, float z);
void silentRenderIndices();
#endif
