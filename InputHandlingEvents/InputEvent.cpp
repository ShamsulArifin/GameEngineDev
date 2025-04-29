#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS; // in ms

const SDL_Color WHITE = {255, 255, 255, 255};

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
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
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
	TTF_Font *font = TTF_OpenFont("lucon.ttf", 12);
	if (!font)
	{
		std::cerr << "Failed to load font" << SDL_GetError() << std::endl;
	}

	// Main game loop
	bool isRunning = true;
	SDL_Event event;

	// deltaTime
	Uint32 lastTime = SDL_GetTicks(); // milisecond

	// demo object
	float rectX = 0.0f, speed = 300.0f; // pixels per second

	while (isRunning)
	{
		// deltaTime calculation
		Uint32 currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f; // converts ms to s
		if (deltaTime < FRAME_DELAY)
		{
			SDL_Delay(FRAME_DELAY - deltaTime);
		}
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
		if (rectX > 800)
			rectX = 0;

		// Render
		SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
		SDL_RenderClear(renderer);

		// stats
		std::string fpsText = "FPS: " + std::to_string((int)fps);
		std::string deltaTimeText = "Delta time: " + std::to_string((float)deltaTime);
		std::string speedText = "Delta time: " + std::to_string((float)speed);

		SDL_Surface *surface_fps = TTF_RenderText_Solid(font, fpsText.c_str(), fpsText.length(), WHITE);
		SDL_Surface *surface_deltaTime = TTF_RenderText_Solid(font, deltaTimeText.c_str(), deltaTimeText.length(), WHITE);
		SDL_Surface *surface_speed = TTF_RenderText_Solid(font, speedText.c_str(), speedText.length(), WHITE);

		SDL_Texture *texture_fps = SDL_CreateTextureFromSurface(renderer, surface_fps);
		SDL_Texture *texture_deltaTime = SDL_CreateTextureFromSurface(renderer, surface_deltaTime);
		SDL_Texture *texture_speed = SDL_CreateTextureFromSurface(renderer, surface_speed);

		SDL_FRect dstRect_fps = {10.0f, 10.0f, static_cast<float>(surface_fps->w), static_cast<float>(surface_fps->h)};
		SDL_FRect dstRect_deltaTime = {10.0f, 30.0f, static_cast<float>(surface_deltaTime->w), static_cast<float>(surface_deltaTime->h)};
		SDL_FRect dstRect_speed = {10.0f, 50.0f, static_cast<float>(surface_speed->w), static_cast<float>(surface_speed->h)};

		SDL_RenderTexture(renderer, texture_fps, nullptr, &dstRect_fps);
		SDL_RenderTexture(renderer, texture_deltaTime, nullptr, &dstRect_deltaTime);
		SDL_RenderTexture(renderer, texture_speed, nullptr, &dstRect_speed);

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