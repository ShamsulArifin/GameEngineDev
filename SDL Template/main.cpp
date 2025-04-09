#include <iostream>
#include <SDL3/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *Window = SDL_CreateWindow("Hello world!", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

	if (NULL == Window)
	{
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Event windowEvent;

	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (SDL_EVENT_QUIT == windowEvent.type)
			{
				break;
			}
		}
	}

	SDL_DestroyWindow(Window);
	SDL_Quit();

	return EXIT_SUCCESS;
}