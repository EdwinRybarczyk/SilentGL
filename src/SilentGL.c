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
		vao->vboCount++;
	}

	//Indices will always be loaded into second vbo in a vao
	else if(vbo->vboType == SILENT_VBO_INDICE)
	{
		vao->vbo[1] = *vbo;
		vao->vboCount++;
	}
	//Any other data is managed by shaders so no need
	//for the rasterizer to know which is which
	else
	{
		vao->vbo[vao->vboCount++] = *vbo;
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

void setPixel(int x, int y, int z, Colour colour)
{
	//if(silentRasterizer->zBuffer[
	//	y*silentRasterizer->width + x
	//] < x)
	{

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
			12
		);
		iterator += 1;
		silentRasterizer->vertexShader(&v0);

		memcpy(&v1,&silentRasterizer->vao->vbo[0].floatingPoint[
			silentRasterizer->vao->vbo[1].integer[iterator]*3],
			12
		);
		iterator += 1;
		silentRasterizer->vertexShader(&v1);

		memcpy(&v2,&silentRasterizer->vao->vbo[0].floatingPoint[
			silentRasterizer->vao->vbo[1].integer[iterator]*3],
			12
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
		minx = (int)(min3f(v0.x,v1.x,v2.x));
		maxx = (int)(max3f(v0.x,v1.x,v2.x));
		miny = (int)(min3f(v0.y,v1.y,v2.y));
		maxy = (int)(max3f(v0.y,v1.y,v2.y));

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
		//v0.z = 1/v0.z; v1.z = 1/v1.z; v2.z = 1/v2.z;

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
				cx1++;
				cx2 = c2y * (x - v1.x);
				cx2++;
				cx3 = c3y * (x - v2.x);
				cx3++;

				
				if((cy1 < cx1)&&(cy2 < cx2)&&(cy3 < cx3))
				{
					//Calculate baryocentric coordinates
					//cx1 = ((cx1-cy1)/zArea);
					//cx2 = ((cx2-cy2)/zArea);
					//cx3 = ((cx3-cy3)/zArea);

					//Calculate Z buffer
					//z = 1/((v0.z * cx2) + (v1.z * cx3) + (v2.z * cx1));

					//cx1 *= z;
					//cx2 *= z;
					//cx3 *= z;

					//Colour colour = silentRasterizer->fragmentShader();
					Colour colour = {255,255,255};
					//Colour the triangle
					setPixel(x,y,z,colour);
				}
				
			}
		}
	}
}
