#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL couldn't initialize! SDL_Error: " << SDL_GetError() << "\n";
		return -1;
	}

	// Initialize SDL3_ttf
	if (TTF_Init() != 0)
	{
		std::cerr << "TTF_Init failed: " << SDL_GetError() << std::endl;
	}

	// Create window
	SDL_Window *window = SDL_CreateWindow(
			"Game Loop Window",
			800,
			600,
			SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		std::cerr << "Window creation failed! SDL_Error: " << SDL_GetError() << "\n";

		SDL_Quit();
		return -1;
	}

	// Create renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer)
	{
		std::cerr << "Renderer creation failed! SDL_Error: " << SDL_GetError() << "\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	// load font
	TTF_Font *font = TTF_OpenFont("lucon.ttf", 24);
	if (!font)
	{
		std::cerr << "Failed to load font" << SDL_GetError() << std::endl;
	}

	// Main game loop
	bool isRunning = true;
	SDL_Event event;

	// deltaTime
	Uint32 lastTime = SDL_GetTicks();  // milisecond

	// demo object
	float rectX = 0.0f, speed = 300.0f;  // pixels per second


	while (isRunning)
	{
		// deltaTime calculation
		Uint32 currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f;  // converts ms to s
		lastTime = currentTime;

		float fps = 1.0f / deltaTime;

		std::cout << "deltaTime: " << deltaTime << " sec\n";

		// input
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE))
			{
				isRunning = false;
			}
		}

		// Update demo object (framerate - independent)
		rectX += speed * deltaTime;

		// Wrap around when off screen
		if(rectX > 800)
			rectX = 0;

		// Render
		SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
		SDL_RenderClear(renderer);

		// FPS text
		std::string fpsText = "FPS: " + std::to_string((int)fps);
		SDL_Color white =  {255, 255, 255, 255};

		SDL_Surface *surface = TTF_RenderText_Solid(font, fpsText.c_str(), fpsText.length(), white);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FRect dstRect = {10.0f, 10.0f, static_cast<float>(surface->w), static_cast<float>(surface->h)};
		SDL_RenderTexture(renderer, texture, nullptr, &dstRect);

		SDL_FRect rect = {static_cast<float>(rectX), 250, 100, 100};
		SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);
	}

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}