#include <SDL2/SDL.h>
#include "SilentGL.h"
#include "objLoader.h"

//shaders
void vertexShader(vec3f* v)
{
	//v->x += 0.5;
	v->z += 2;
	//printf("%f %f %f\n",v->x,v->y,v->z);
}

Colour fragmentShader()
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

	//SDL_Renderer* renderer = SDL_CreateRenderer(
	//window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
	
	SDL_Renderer* renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_PRESENTVSYNC);
		
	SDL_Texture* texture = SDL_CreateTexture(
		renderer, SDL_PIXELFORMAT_RGB888,
		SDL_TEXTUREACCESS_STREAMING,screenWidth,screenHeight);

	SDL_SetRenderDrawColor(renderer,0,0,0,255);

	SDL_Event event;

	//Rasterizer test
	createSilentRasterizer(screenWidth,screenHeight);
	char* pixels = silentGetRenderBuffer();
	
	//Loading data
	//Load object
	objData model = loadModelOBJ("untitled.obj");
	//Load shaders
	silentLoadVertexShader(vertexShader);
	silentLoadFragmentShader(fragmentShader);
	//Create VAO
	SilentVertexArray* vao = silentCreateVao(2);
	//Create vertex VBO
	SilentVertexBuffer* vert = 
		silentCreateVbo(SILENT_VBO_VERTEX,model.vCount/**sizeof(float)*/);
	vert->floatingPoint = model.vertices;
	//Create indice VBO
	SilentVertexBuffer* ind = 
		silentCreateVbo(SILENT_VBO_INDICE,model.iCount/**sizeof(int)*/);
	ind->integer = model.indices;
	//for(int i = 0; i < model.iCount; i++)
	//{
	//	printf("%f\n",vert->floatingPoint[
	//		ind->integer[i]*3
	//	]);
	//}
	//Load VAO to rasterizer
	silentLoadVao(vao);
	//Load the 2 VBOs
	silentLoadVbo(vao,vert);
	silentLoadVbo(vao,ind);
	
	
	
	//Main loop
	char running = 1;
	//while(running)
	for(int i = 0; i < 60; i++)
	{
		//SDL event stuff
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT){running = 0;break;}
		}
	
		//Rasterizing
		silentRenderIndices();
		//SDL stuff
		SDL_UpdateTexture(texture,NULL,pixels,screenWidth * 4);
		SDL_RenderCopy(renderer,texture,NULL,NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
		SDL_RenderClear(renderer);
		//Clear the buffer
		memset(pixels,0,screenWidth * screenHeight * 4);
		//printf("done frame\n");
	}
	
	//free(model.vertices);
	//model.vertices = NULL;
	//free(model.indices);
	//model.indices = NULL;
	//free(model.normals);
	//model.normals = NULL;
	//free(model.textureCoords);
	//model.textureCoords = NULL;
	deleteSilentRasterizer();
	//SDL_DestroyWindow(window);

	//deleteSilentRasterizer();
	return 0;
}
