#include <SDL3/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char *argv[])
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL couldn't initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Create window
	SDL_Window *window = SDL_CreateWindow(
			"Template",                 // change title
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		std::cerr << "Window creation failed! SDL_Error: " << SDL_GetError() << std::endl;

		SDL_Quit();
		return -1;
	}

	// Create renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer)
	{
		std::cerr << "Renderer creation failed! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	// Main game loop
	bool isRunning = true;
	SDL_Event event;

	while (isRunning)
	{
		// input
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE))
			{
				isRunning = false;
			}
		}
		// Render
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}