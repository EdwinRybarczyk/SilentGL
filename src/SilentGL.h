typedef struct vec2i
{
	int x,y;
}vec2i;

typedef struct vec2f
{
	float x,y;
}vec2f;

typedef struct vec3i
{
	int x,y,z;
}vec3i;

typedef struct vec3f
{
	float x,y,z;
}vec3f;

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
void silentRenderIndices();
