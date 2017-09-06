#include <stdio.h>
#include "SDL.h"
#include "SilentScreen.h"
#include "SilentRasterizer.h"
#undef main


int main() 
{
	unsigned int width = 500;
	unsigned int height = 500;
	char* title = "test";
	SilentScreen* screen = createSilentScreen(width, height);
	SilentRasterizer* rasterizer = createSilentRasterizer(screen);

	//SDL setup
	if (SDL_Init(SDL_INIT_VIDEO) == -1) { printf("failed to initialise SDL!\n"); return -1; }
	SDL_Window* window = SDL_CreateWindow(
		title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		width, height);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Event event;

	char running = 1;
	char* vertices = malloc(100);

	while (running) 
	{
		while (SDL_PollEvent(&event)) { if (event.type == SDL_QUIT) { running = 0; break; } }

		rasterizeTriangle(rasterizer, vertices);

		SDL_UpdateTexture(texture, NULL, screen->pixels + 0, width * 4);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		SDL_RenderClear(renderer);
	}
}