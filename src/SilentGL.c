#include "SilentGL.h"
#include <stdlib.h>
void createSilentRasterizer(int screenWidth, int screenHeight)
{
	silentRasterizer = malloc(sizeof(SilentRasterizer));
	silentRasterizer->pixels = malloc(screenWidth*screenHeight*4);
	silentRasterizer->width = screenWidth;
	silentRasterizer->height = screenHeight;
}

void deleteSilentRasterizer()
{
	free(silentRasterizer->pixels);
	free(silentRasterizer);
}

SilentRasterizer* getSilentRasterizerRef()
{
	return silentRasterizer;
}

char* silentGetRenderBuffer()
{
	return silentRasterizer->pixels;
}


float min(float x, float y, float z)
{
	float minimum = x;
	if(y<minimum){minimum=y;}
	if(z<minimum){minimum=z;}
	return minimum;
}

float max(float x, float y, float z)
{
	float maximum = x;
	if(y>maximum){maximum=y;}
	if(z>maximum){maximum=z;}
	return maximum;

}

void silentLoadVertexCoordinates(vec3f** vertex, int vertexCount)
{
	silentRasterizer->vertices = malloc(sizeof(vec3f*)*vertexCount);
	silentRasterizer->vertices = vertex;
	silentRasterizer->vertexCount = vertexCount;
}

void silentLoadIndices(int* indices, int indiceCount)
{
	silentRasterizer->indices = indices;
	silentRasterizer->indiceCount = indiceCount;
}

void setPixel(int x, int y,char r, char g, char b)
{
	x = (x * 4) + (y * silentRasterizer->width*4);
	silentRasterizer->pixels[x] = b;
	silentRasterizer->pixels[x + 1] = g;
	silentRasterizer->pixels[x + 2] = r;
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

	while(iterator < silentRasterizer->indiceCount)
	{
		v0 = *silentRasterizer->vertices[silentRasterizer->indices[iterator++]];
		v1 = *silentRasterizer->vertices[silentRasterizer->indices[iterator++]];
		v2 = *silentRasterizer->vertices[silentRasterizer->indices[iterator++]];

		//Convert to raster space
		halfWidth = (0.5 * silentRasterizer->width);
		halfHeight = (0.5 * silentRasterizer->height);


		v0.x = halfWidth - (-v0.x * halfWidth);
		v0.y = halfHeight - (v0.y * halfHeight);

		v1.x = halfWidth - (-v1.x * halfWidth);
		v1.y = halfHeight - (v1.y * halfHeight);

		v2.x = halfWidth - (-v2.x * halfWidth);
		v2.y = halfHeight - (v2.y * halfHeight);


		//Rasterize triangle
		
		//Calculate bounding rectangle
		minx = (int)(min(v0.x,v1.x,v2.x));
		maxx = (int)(max(v0.x,v1.x,v2.x));
		miny = (int)(min(v0.y,v1.y,v2.y));
		maxy = (int)(max(v0.y,v1.y,v2.y));

		//Assign X constants for the triangle
		c1x = v1.x - v0.x;
		c2x = v2.x - v1.x;
		c3x = v0.x - v2.x;

		//Assign Y constants for the triangle
		c1y = v1.y - v0.y;
		c2y = v2.y - v1.y;
		c3y = v0.y - v2.y;
		
		//zBufferArea
		v0.z = 1/v0.z; v1.z = 1/v1.z; v2.z = 1/v2.z;
		float zArea = (c1x * (v2.y - v0.y)) - (c1y * (v2.x-v0.x));
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
					cx1 = (cx1-cy1)/-zArea;
					cx2 = (cx2-cy2)/-zArea;
					cx3 = (cx3-cy3)/-zArea;

					//Calculate Z buffer
					float z = 1/((v0.z * cx1) + (v1.z * cx2) + (v2.z * cx3));

					//Colour the triangle
					setPixel(x,y,255*cx1,255*cx2,255*cx3);
				}
			}
		}
	}
}
