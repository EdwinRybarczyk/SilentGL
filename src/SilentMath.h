#include <stdlib.h>
#ifndef SILENT_MATH
#define SILENT_MATH
//2 integer vector
typedef struct vec2i
{
	int x,y;
}vec2i;

vec2i* createVec2i(int x, int y);

//2 float vector
typedef struct vec2f
{
	float x,y;
}vec2f;

vec2f* createVec2f(float x, float y);

//3 integer vector
typedef struct vec3i
{
	int x,y,z;
}vec3i;

vec3i* createVec3i(int x, int y, int z);

//3 float vector
typedef struct vec3f
{
	float x,y,z;
}vec3f;

vec3f createVec3f(float x, float y, float z);

//4 integer vector
typedef struct vec4i
{
	int x,y,z,w;
}vec4i;

vec4i* createVec4i(int x, int y, int z, int w);

//4 float vector
typedef struct vec4f
{
	float x,y,z,w;
}vec4f;

vec4f* createVec4f(float x, float y, float z, float w);

//Integer matrix 4x4
typedef struct mat4i
{
	int mat[4][4];
}mat4i;

mat4i* createMat4i();

//Float matrix 4x4
typedef struct mat4f
{
	float mat[4][4];
}mat4f;

mat4f* createMat4f();
mat4f* createIdentity();

//Smallest value out of 3 floats
float min3f(float x, float y, float z);
//Largest value out of 3 floats
float max3f(float x, float y, float z);
//Smallest value out of 3 integers
int min3i(int x, int y, int z);
//Largest value out of 3 integers
int max3i(int x, int y, int z);


void multiplyVec4fMat4f(vec4f *vec,mat4f *mat);
void addVec4f(vec4f *vec, mat4f* mat);

#endif
