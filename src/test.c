#include <SDL2/SDL.h>
#include "SilentGL.h"

//shaders
void vertexShader(SilentVertexArray* vao)
{
	//printf("%i\n",vao->vbo);
}

Colour fragmentShader(SilentVertexArray* vao)
{
	Colour c = {0,255,255};
	return c;
}

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
	//declare data
	int c = 0;
	vec3f *vertex = malloc(sizeof(vec3f) * 4);
	vertex[c++] = createVec3f(0,0.5,2);
	vertex[c++] = createVec3f(-0.5,0,5);
	vertex[c++] = createVec3f(0.5,0,2);
	vertex[c++] = createVec3f(0.5,0.5,2);

	c = 0;
	int *indices = malloc(sizeof(int) * 6);
	indices[c++] = 0;
	indices[c++] = 1;
	indices[c++] = 2;
	indices[c++] = 0;
	indices[c++] = 2;
	indices[c++] = 3;



	//Loading data
	silentLoadVertexShader(vertexShader);
	silentLoadFragmentShader(fragmentShader);
	SilentVertexArray* vao = silentCreateVao(2);
	SilentVertexBuffer* vert = silentCreateVbo(SILENT_VBO_VERTEX,4);
	vert->vector3f = vertex;
	SilentVertexBuffer* ind = silentCreateVbo(SILENT_VBO_INDICE,3);
	ind->integer = indices;
	silentLoadVao(vao);
	silentLoadVbo(vao,vert);
	silentLoadVbo(vao,ind);
	

	//Main loop
	char running = 1;
	while(running)
	//for(int i = 0; i < 60; i++)
	{
		//SDL event stuff
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT){running = 0;break;}
		}
	
		//Rasterizing
		silentRenderIndices();
//		silentTranslate(0,0.0,0.02);
		//SDL stuff
		SDL_UpdateTexture(texture,NULL,pixels,screenWidth * 4);
		SDL_RenderCopy(renderer,texture,NULL,NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(0);
		SDL_RenderClear(renderer);
		//Clear the buffer
		memset(pixels,0,screenWidth * screenHeight * 4);
	}
	
	free(vertex);
	vertex = NULL;
	free(indices);
	indices = NULL;
	free(vert);
	vert = NULL;
	free(ind);
	ind = NULL;
	deleteSilentRasterizer();
	SDL_DestroyWindow(window);

	//deleteSilentRasterizer();
	return 0;
}
