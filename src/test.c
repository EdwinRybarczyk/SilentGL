#include <SDL2/SDL.h>
#include "SilentGL.h"
/*
vec3f* createVec3f(float x, float y, float z)
{
	
	vec3f* vec = malloc(sizeof(vec3f));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return vec;
}*/

int main()
{
	int screenWidth = 640;
	int screenHeight = 480;
	char* title = "Hey barbeque, michael here";

	//SDL init
	SDL_Window* window = SDL_CreateWindow(
		title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth,screenHeight, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(
		window, -1, /*SDL_RENDERER_ACCELERATED ||*/ SDL_RENDERER_PRESENTVSYNC);
		
	SDL_Texture* texture = SDL_CreateTexture(
		renderer, SDL_PIXELFORMAT_RGB888,
		SDL_TEXTUREACCESS_STREAMING,screenWidth,screenHeight);

	SDL_SetRenderDrawColor(renderer,0,0,0,255);

	SDL_Event event;

	//Rasterizer test
	createSilentRasterizer(screenWidth,screenHeight);
	char* pixels = silentGetRenderBuffer();
	
	int c = 0;
	vec3f **vertex = malloc(sizeof(vec3f*) * 4);
	vertex[c++] = createVec3f(0,0.5,5);
	vertex[c++] = createVec3f(-0.5,0,5);
	vertex[c++] = createVec3f(0.5,0,10);
	vertex[c++] = createVec3f(0.5,0.5,0.9);

	c = 0;
	int *indices = malloc(sizeof(int) * 6);
	indices[c++] = 0;
	indices[c++] = 1;
	indices[c++] = 2;
	indices[c++] = 0;
	indices[c++] = 2;
	indices[c++] = 3;

	silentLoadVertexCoordinates(vertex,4);
	silentLoadIndices(indices,3);
	//silentTranslate(-1,0,0.4);
	silentApplyProjection(90,0.1,10);

	//Main loop
	char running = 1;
	while(running)
	{
		//SDL event stuff
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT){running = 0;break;}
		}
	
		//Rasterizing
		silentRenderIndices();
		//silentTranslate(0,0.001,0.1);
		//SDL stuff
		SDL_UpdateTexture(texture,NULL,pixels,screenWidth * 4);
		SDL_RenderCopy(renderer,texture,NULL,NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
		SDL_RenderClear(renderer);
		//Clear the buffer
		memset(pixels,0,screenWidth * screenHeight * 4);
	}

	deleteSilentRasterizer();
	return 0;
}
