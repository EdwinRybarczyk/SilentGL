#include <SDL2/SDL.h>
#include "SilentGL.h"
#include "objLoader.h"

char va = 0;
//shaders
void vertexShader(vec3f* v)
{
	//v->x += 0.5;
	if(va == 0)
	{
		//v->y += 2;
		//v->z += 2;
		v->x += 0.25;
		v->z -= 0.5;
	}
	else
	{
		v->x -= 0.25;
		 //c.r = 255;
	}
	v->z += 2;
	//printf("%f %f %f\n",v->x,v->y,v->z);
}

Colour fragmentShader()
{
	Colour c;
	if(va == 0)
	{
		c.b = 255;
		c.r = 0;
		c.g = 0;
	}
	else
	{
		 c.r = 255;
		 c.b = 0;
		 c.g = 0;
	}
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
	objData model = loadModelOBJ("untitled1.obj");
	//objData model2 = loadModelOBJ("untitled1.obj");
	//Load shaders
	silentLoadVertexShader(vertexShader);
	silentLoadFragmentShader(fragmentShader);
	//Create VAO
	SilentVertexArray* vao = silentCreateVao(2);
	//Create vertex VBO
	SilentVertexBuffer* vert = 
		silentCreateVbo(SILENT_VBO_VERTEX,model.vCount*sizeof(float));
	vert->floatingPoint = model.vertices;
	//Create indice VBO
	SilentVertexBuffer* ind = 
		silentCreateVbo(SILENT_VBO_INDICE,model.iCount*sizeof(int));
	ind->integer = model.indices;

	
	/*
	//Create VAO2
	SilentVertexArray* vao2 = silentCreateVao(2);
	//Create vertex VBO2
	SilentVertexBuffer* vert2 = 
		silentCreateVbo(SILENT_VBO_VERTEX,model2.vCount*sizeof(float));
	vert2->floatingPoint = model2.vertices;
	//Create indice VBO2
	SilentVertexBuffer* ind2 = 
		silentCreateVbo(SILENT_VBO_INDICE,model2.iCount*sizeof(int));
	ind2->integer = model2.indices;
	*/
	silentLoadVao(vao);
	//Load the 2 VBOs
	silentLoadVbo(vao,vert);
	silentLoadVbo(vao,ind);
	//silentLoadVbo(vao2,vert2);
	//silentLoadVbo(vao2,ind2);
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
	
		//Load obj1
		//va = 0;
		silentLoadVao(vao);
		silentRenderIndices();
		//Load obj2
		//va = 1;
		//silentLoadVao(vao2);
		//silentRenderIndices();
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
	
	free(model.vertices);
	model.vertices = NULL;
	free(model.indices);
	model.indices = NULL;
	free(model.normals);
	model.normals = NULL;
	free(model.textureCoords);
	model.textureCoords = NULL;
	deleteSilentRasterizer();
	SDL_DestroyWindow(window);

	//deleteSilentRasterizer();
	return 0;
}
