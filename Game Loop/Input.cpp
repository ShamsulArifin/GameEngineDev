#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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
	bool bgToggle = false;

	while (isRunning)
	{
		// input
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE))
			{
				isRunning = false;
			}
			if (event.type = SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP)
			{
				bool down = (event.type == SDL_EVENT_KEY_DOWN);
				SDL_Keycode Key = event.key.key;

				switch (Key)
				{
					case SDLK_W: 
						std::cout << (down ? "W Down\n" : "W up\n");
					break;
					case SDLK_A: 
						std::cout << (down ? "A Down\n" : "A up\n");
					break;
					case SDLK_S: 
						std::cout << (down ? "S Down\n" : "S up\n");
					break;
					case SDLK_D: 
						std::cout << (down ? "D Down\n" : "D up\n");
					break;
					case SDLK_SPACE:
						if (down)
							bgToggle = !bgToggle;
						break;
					default:
					break;
				}
			}

			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				std::cout << "Mouse Clicked at: " << x << ", " << y << std::endl;
			}
		}

		// Render
		SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
		SDL_RenderClear(renderer);
	}

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}