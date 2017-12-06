#include "SilentGL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
void createSilentRasterizer(int screenWidth, int screenHeight)
{
	silentRasterizer = malloc(sizeof(SilentRasterizer));
	silentRasterizer->pixels = malloc(screenWidth*screenHeight*4);
	silentRasterizer->zBuffer = malloc(screenWidth*screenHeight*4);
	//Trust it works
	memset(silentRasterizer->zBuffer,127,screenWidth*screenHeight*4);
	silentRasterizer->width = screenWidth;
	silentRasterizer->height = screenHeight;
}

void deleteSilentRasterizer()
{
	free(silentRasterizer->vao->vbo);
	silentRasterizer->vao->vbo = NULL;
	free(silentRasterizer->vao);
	silentRasterizer->vao = NULL;
	free(silentRasterizer->pixels);
	silentRasterizer->pixels = NULL;
}

SilentRasterizer* getSilentRasterizerRef()
{
	return silentRasterizer;
}

char* silentGetRenderBuffer()
{
	return silentRasterizer->pixels;
}

SilentVertexBuffer* silentCreateVbo(SilentVboType type,long size)
{
	SilentVertexBuffer* vbo = malloc(sizeof(SilentVertexBuffer));
	vbo->vboType = type;
	vbo->vboCount = size;
	vbo->vboCounter = 0;
	return vbo;
}

SilentVertexArray* silentCreateVao(int size)
{
	SilentVertexArray* vao = malloc(sizeof(SilentVertexArray));
	vao->vbo = malloc(sizeof(SilentVertexBuffer) * size);
	vao->vboCount = 0;
	return vao;
}

void silentLoadVao(SilentVertexArray* vao)
{
	silentRasterizer->vao = vao;
}

void silentLoadVbo(SilentVertexArray* vao, SilentVertexBuffer* vbo)
{
	//Vertex will always be loaded into first vbo in a vao
	if(vbo->vboType == SILENT_VBO_VERTEX)
	{
		vao->vbo[0] = *vbo;
		vao->vboCount+=1;
	}

	//Indices will always be loaded into second vbo in a vao
	else if(vbo->vboType == SILENT_VBO_INDICE)
	{
		vao->vbo[1] = *vbo;
		vao->vboCount+=1;
	}
	//Any other data is managed by shaders so no need
	//for the rasterizer to know which is which
	else
	{
		vao->vbo[vao->vboCount+=1] = *vbo;
	}
}

void silentLoadVertexShader(vsp shader)
{
	silentRasterizer->vertexShader = shader;
}

void silentLoadFragmentShader(fsp shader)
{
	silentRasterizer->fragmentShader = shader;
}

void setPixel(int x, int y, float z, Colour colour)
{
	if(silentRasterizer->zBuffer[
		y*silentRasterizer->width + x
	] >= z && z >= 0)	
	{
		silentRasterizer->zBuffer[
			y*silentRasterizer->width + x
		] = z;
		if(!((x > silentRasterizer->width || x < 0) &&
			(y > 0 && y < silentRasterizer->height)) )
		{
			x = (x * 4) + (y * silentRasterizer->width*4);
			silentRasterizer->pixels[x] = colour.b;
			silentRasterizer->pixels[x + 1] = colour.g;
			silentRasterizer->pixels[x + 2] = colour.r;
		}
	}
}

void silentRenderIndices2()
{
	int iterator = 0;

	//prepare space for vertices
	vec3f v0;
	vec3f v1;
	vec3f v2;

	int minx,maxx,miny,maxy;

	float c1x,c2x,c3x;
	float c1y,c2y,c3y;

	float cy1,cy2,cy3;
	float cx1,cx2,cx3;

	float halfWidth, halfHeight;

	float d2r = M_PI/180;

	while(iterator < silentRasterizer->vao->vbo[1].vboCount)
	{
		memcpy(&v0,&silentRasterizer->vao->vbo[0].floatingPoint[
			silentRasterizer->vao->vbo[1].integer[iterator]*3],
			3*sizeof(float)
		);
		iterator += 1;
		silentRasterizer->vertexShader(&v0);

		memcpy(&v1,&silentRasterizer->vao->vbo[0].floatingPoint[
			silentRasterizer->vao->vbo[1].integer[iterator]*3],
			3*sizeof(float)
		);
		iterator += 1;
		silentRasterizer->vertexShader(&v1);

		memcpy(&v2,&silentRasterizer->vao->vbo[0].floatingPoint[
			silentRasterizer->vao->vbo[1].integer[iterator]*3],
			3*sizeof(float)
		);
		iterator += 1;
		silentRasterizer->vertexShader(&v2);

		v0.x /= v0.z; v0.y /= v0.z;
		v1.x /= v1.z; v1.y /= v1.z;
		v2.x /= v2.z; v2.y /= v2.z;

		//Convert to raster space
		halfWidth = (0.5 * silentRasterizer->width);
		halfHeight = (0.5 * silentRasterizer->height);
	
		v0.x = (halfWidth - (-v0.x * halfWidth));
		v0.y = (halfHeight - (v0.y * halfHeight));

		v1.x = (halfWidth - (-v1.x * halfWidth));
		v1.y = (halfHeight - (v1.y * halfHeight));


		v2.x = (halfWidth - (-v2.x * halfWidth));
		v2.y = (halfHeight - (v2.y * halfHeight));

		//Calculate bounding rectangle
		minx = (int)ceil(min3f(v0.x,v1.x,v2.x));
		maxx = (int)ceil(max3f(v0.x,v1.x,v2.x));
		miny = (int)ceil(min3f(v0.y,v1.y,v2.y));
		maxy = (int)ceil(max3f(v0.y,v1.y,v2.y));

		c1x = v0.x - v1.x; c1y = v1.y - v0.y;
		c2x = v1.x - v2.x; c2y = v2.y - v1.y;
		c3x = v2.x - v0.x; c3y = v0.y - v2.y;

		float r1 = (v1.x-v2.x)*(miny-v1.y)-(v1.y-v2.y)*(minx-v1.x);
		float r2 = (v2.x-v0.x)*(miny-v2.y)-(v2.y-v0.y)*(minx-v2.x);
		float r3 = (v0.x-v1.x)*(miny-v0.y)-(v0.y-v1.y)*(minx-v0.x);

		float zArea = (-((c1x * (v2.y - v0.y)) - (c1y * (v2.x-v0.x))));
		v0.z = 1/v0.z; v1.z = 1/v1.z; v2.z = 1/v2.z;

		int y;
		int x;
		
		for(y = miny; y < maxy; y++)
		{
			float f1 = r1;
			float f2 = r2;
			float f3 = r3;
			for(x = minx; x < maxx; x++)
			{

				if(f1 >= 0 && f2 >= 0 && f3 >= 0)
				{
					float w1 = f1/zArea;
					float w2 = f2/zArea;
					float w3 = f3/zArea;

					float z = 1;///((v0.z * w1) + (v1.z * w2) + (v2.z * w3));


					Colour colour = silentRasterizer->fragmentShader();
					//Colour the triangle
					colour.b *= 1/z * 3;
					colour.r *= 1/z * 3;
					setPixel(x,y,z,colour);
				}

				f1 += c2x;
				f2 += c3x;
				f3 += c1x;
			}
			r1 += c2y;
			r2 += c3y;
			r3 += c1y;
		}

	}
}

void silentRenderIndices()
{
	int iterator = 0;

	//prepare space for vertices
	vec3f v0;
	vec3f v1;
	vec3f v2;

	int minx,maxx,miny,maxy;

	float c1x,c2x,c3x;
	float c1y,c2y,c3y;

	float cy1,cy2,cy3;
	float cx1,cx2,cx3;

	float halfWidth, halfHeight;

	float d2r = M_PI/180;

	while(iterator < silentRasterizer->vao->vbo[1].vboCount)
	{
		memcpy(&v0,&silentRasterizer->vao->vbo[0].floatingPoint[
			silentRasterizer->vao->vbo[1].integer[iterator]*3],
			3*sizeof(float)
		);
		iterator += 1;
		silentRasterizer->vertexShader(&v0);

		memcpy(&v1,&silentRasterizer->vao->vbo[0].floatingPoint[
			silentRasterizer->vao->vbo[1].integer[iterator]*3],
			3*sizeof(float)
		);
		iterator += 1;
		silentRasterizer->vertexShader(&v1);

		memcpy(&v2,&silentRasterizer->vao->vbo[0].floatingPoint[
			silentRasterizer->vao->vbo[1].integer[iterator]*3],
			3*sizeof(float)
		);
		iterator += 1;
		silentRasterizer->vertexShader(&v2);

		v0.x /= v0.z; v0.y /= v0.z;
		v1.x /= v1.z; v1.y /= v1.z;
		v2.x /= v2.z; v2.y /= v2.z;

		//Convert to raster space
		halfWidth = (0.5 * silentRasterizer->width);
		halfHeight = (0.5 * silentRasterizer->height);
	
		v0.x = (halfWidth - (-v0.x * halfWidth));
		v0.y = (halfHeight - (v0.y * halfHeight));

		v1.x = (halfWidth - (-v1.x * halfWidth));
		v1.y = (halfHeight - (v1.y * halfHeight));


		v2.x = (halfWidth - (-v2.x * halfWidth));
		v2.y = (halfHeight - (v2.y * halfHeight));

		//Rasterize triangle
		
		//Calculate bounding rectangle
		minx = (int)ceil(min3f(v0.x,v1.x,v2.x));
		maxx = (int)ceil(max3f(v0.x,v1.x,v2.x));
		miny = (int)ceil(min3f(v0.y,v1.y,v2.y));
		maxy = (int)ceil(max3f(v0.y,v1.y,v2.y));

		//Assign X constants for the triangle
		c1x = v1.x - v0.x;
		c2x = v2.x - v1.x;
		c3x = v0.x - v2.x;

		//Assign Y constants for the triangle
		c1y = v1.y - v0.y;
		c2y = v2.y - v1.y;
		c3y = v0.y - v2.y;


		//zBufferArea
		float zArea = (-((c1x * (v2.y - v0.y)) - (c1y * (v2.x-v0.x))));
		v0.z = 1/v0.z; v1.z = 1/v1.z; v2.z = 1/v2.z;

		float z;

		int y;
		int x;
		
		for(y = miny; y < maxy; y++)
		{
			cy1 = c1x * (y - v0.y);
			cy2 = c2x * (y - v1.y);
			cy3 = c3x * (y - v2.y);


			for(x = minx; x < maxx; x++)
			{
				
				cx1 = c1y * (x - v0.x);
				cx2 = c2y * (x - v1.x);
				cx3 = c3y * (x - v2.x);

		
				if((cy1 >= cx1)&&(cy2 >= cx2)&&(cy3 >= cx3))
				//if(e1 >= 0 && e2 >= 0 && e3 >= 0)
				{
					//Calculate baryocentric coordinates
					cx1 = ((cx1-cy1)/zArea);
					cx2 = ((cx2-cy2)/zArea);
					cx3 = ((cx3-cy3)/zArea);

					//e1 /= zArea;
					//e2 /= zArea;
					//e3 /= zArea;

					//Calculate Z buffer
					z = 1/((v0.z * cx2) + (v1.z * cx3) + (v2.z * cx1));

					//cx1 *= z;
					//cx2 *= z;
					//cx3 *= z;

					Colour colour = silentRasterizer->fragmentShader();
					//Colour the triangle
					colour.b *= 1/z * 3;
					colour.r *= 1/z * 3;
					setPixel(x,y,z,colour);
				}
			}
		}
	}
}
