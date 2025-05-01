#include <SDL3/SDL.h>
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char *argv[])
{
	// * Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL couldn't initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	// * Create window
	SDL_Window *window = SDL_CreateWindow(
			"Rendering Part 2", // * change title
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		std::cerr << "Window creation failed! SDL_Error: " << SDL_GetError() << std::endl;

		SDL_Quit();
		return -1;
	}

	// * Create renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer)
	{
		std::cerr << "Renderer creation failed! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	// * Main game loop
	bool isRunning = true;
	SDL_Event event;

	float angle = 0.0f;

	// * Event tick
	Uint64 now = SDL_GetTicks();
	Uint64 last = now;
	double deltaTime = 0;

	while (isRunning)
	{
		last = now;
		now = SDL_GetTicks();
		deltaTime = (now - last) / 1000.0;
		// input
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE))
			{
				isRunning = false;
			}
		}

		angle += 90 * deltaTime;  // * rotate 90° per second

		// * Render
		SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
		SDL_RenderClear(renderer);

		// * Draw filled rect (player)
		SDL_FRect playerRect = { 100, 100, 100, 100 };
		SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);
		SDL_RenderFillRect(renderer, &playerRect);

		// * Draw a line (laser or direction)
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderLine(renderer, 150, 150, 400, 400);

		// * Rotating rectangle
		SDL_FRect rotatingRect = { 400, 250, 80, 80 };
		SDL_SetRenderDrawColor(renderer, 0, 120, 255, 200);
		SDL_RenderGeometry(renderer, nullptr, nullptr, 0, nullptr, 0);  // * placeholder

		SDL_RenderTextureRotated(renderer, nullptr, nullptr, &rotatingRect, angle, nullptr, SDL_FLIP_NONE);  // ! if using this texture

		SDL_RenderPresent(renderer);

		SDL_Delay(16);  // ! ~60 FPS
	}

	// * Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}