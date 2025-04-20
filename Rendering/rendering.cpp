#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <cstring>

const int WIDTH = 800, HEIGHT = 600;
const SDL_Color WHITE = {255, 255, 255, 255};

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *Window = SDL_CreateWindow("Render Test!", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

	if (NULL == Window)
	{
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return 1;
	}

	if(TTF_Init() != 0)
	{
		SDL_Log("TTF_Init failed! SDL_Error: %s", SDL_GetError());
	}

	TTF_Font *font = TTF_OpenFont("lucon.ttf", 12);

	SDL_Surface* imageSurface = SDL_LoadBMP("assets/sample.bmp");

	if(!imageSurface)
	{
		SDL_Log("Failed to load image: %s", SDL_GetError());
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(Window, NULL);

	if(!renderer)
	{
		SDL_Log("Renderer creation failed! SDL_Error: %s", SDL_GetError());
	}

	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
		SDL_DestroySurface(imageSurface);
		if(!imageTexture)
		{
			SDL_Log("Texture creation failed! SDL_Error: %s", SDL_GetError());
			return 1;
		}

	bool isRunning = true;
	SDL_Event event;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE))
			{
				isRunning = false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 50,50,50,255);
		SDL_RenderClear(renderer);

		
		SDL_FRect rect = {100.0f, 100.0f, 200.0f, 150.0f};
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_FRect imgRect = {400.0f, 200.0f, 200.0f, 200.0f};
		SDL_RenderTexture(renderer, imageTexture, NULL, &imgRect);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderLine(renderer, 0, 0, 800, 600);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(imageTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();

	return 0;
}