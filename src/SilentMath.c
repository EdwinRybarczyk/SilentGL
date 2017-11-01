#include "SilentMath.h"
vec2i* createVec2i(int x, int y)
{
	vec2i *vec = malloc(sizeof(vec2i));
	vec->x = x;
	vec->y = y;
	return vec;
}

vec2f* createVec2f(float x, float y)
{
	vec2f *vec = malloc(sizeof(vec2f));
	vec->x = x;
	vec->y = y;
	return vec;
}

vec3i* createVec3i(int x, int y, int z)
{
	vec3i *vec = malloc(sizeof(vec3i));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return vec;
}

vec3f createVec3f(float x, float y, float z)
{
	vec3f vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

vec4i* createVec4i(int x, int y, int z, int w)
{
	vec4i *vec = malloc(sizeof(vec4i));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	vec->w = w;
	return vec;
}
vec4f* createVec4f(float x, float y, float z, float w)
{
	vec4f *vec = malloc(sizeof(vec4f));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	vec->w = w;
	return vec;
}

mat4i* createMat4i()
{
	mat4i mat;
	return &mat;
}

mat4f* createMat4f()
{
	mat4f mat;
	return &mat;
}

float min3f(float x, float y, float z)
{
	float minimum = x;
	if(y<minimum){minimum=y;}
	if(z<minimum){minimum=z;}
	return minimum;
}

float max3f(float x, float y, float z)
{
	float maximum = x;
	if(y>maximum){maximum=y;}
	if(z>maximum){maximum=z;}
	return maximum;
}

int min3i(int x, int y, int z)
{
	int minimum = x;
	if(y<minimum){minimum=y;}
	if(z<minimum){minimum=z;}
	return minimum;
}

int max3i(int x, int y, int z)
{
	int maximum = x;
	if(y>maximum){maximum=y;}
	if(z>maximum){maximum=z;}
	return maximum;
}

