#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <cstring>

const int WIDTH = 800, HEIGHT = 600, TARGET_FPS = 60, FRAME_DELAY = 1000 / TARGET_FPS;
const SDL_Color WHITE = {255, 255, 255, 255};

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *Window = SDL_CreateWindow("Render Test!", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

	if (NULL == Window)
	{
		SDL_Log("Window creation failed! SDL_Error: %s", SDL_GetError());
		return -1;
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
		return -1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(Window, NULL);
	if(!renderer)
	{
		SDL_Log("Renderer creation failed! SDL_Error: %s", SDL_GetError());
		SDL_DestroyWindow(Window);
		SDL_Quit();
		return -1;
	}

	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
		SDL_DestroySurface(imageSurface);
		if(!imageTexture)
		{
			SDL_Log("Texture creation failed! SDL_Error: %s", SDL_GetError());
			return -1;
		}

	bool isRunning = true;
	SDL_Event event;

	Uint32 lastTime = SDL_GetTicks();

	float rectX = 400.0f, speedImage = 300.0f;
	float rectY = 100.0f, speedRect = 200.0f;


	while (isRunning)
	{
		Uint32 currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f;
		if(deltaTime < FRAME_DELAY)
		{
			SDL_Delay(FRAME_DELAY - deltaTime);
		}
		lastTime = currentTime;

		float fps = 1.0f /deltaTime;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE))
			{
				isRunning = false;
			}
		}

		rectX += speedImage * deltaTime;

		if (rectX > 800)
			rectX = 0;

		rectY += speedRect * deltaTime;
		if(rectY > 600)
			rectY = 0;
		
		SDL_SetRenderDrawColor(renderer, 50,50,50,255);
		SDL_RenderClear(renderer);

		
		SDL_FRect rect = {100.0f, static_cast<float>(rectY), 200.0f, 150.0f};
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_FRect imgRect = {static_cast<float>(rectX), 200.0f, 200.0f, 200.0f};
		SDL_RenderTexture(renderer, imageTexture, NULL, &imgRect);

		// stats
		std::string fpsText = "FPS: " + std::to_string((int)fps);
		std::string deltaTimeText = "Delta time: " + std::to_string((float)deltaTime);
		std::string speedImageText = "Image Speed: " + std::to_string((float)speedImage);

		SDL_Surface *surface_fps = TTF_RenderText_Solid(font, fpsText.c_str(), fpsText.length(), WHITE);
		SDL_Surface *surface_deltaTime = TTF_RenderText_Solid(font, deltaTimeText.c_str(), deltaTimeText.length(), WHITE);
		SDL_Surface *surface_speed = TTF_RenderText_Solid(font, speedImageText.c_str(), speedImageText.length(), WHITE);

		SDL_Texture *texture_fps = SDL_CreateTextureFromSurface(renderer, surface_fps);
		SDL_Texture *texture_deltaTime = SDL_CreateTextureFromSurface(renderer, surface_deltaTime);
		SDL_Texture *texture_speed = SDL_CreateTextureFromSurface(renderer, surface_speed);

		SDL_FRect dstRect_fps = {10.0f, 10.0f, static_cast<float>(surface_fps->w), static_cast<float>(surface_fps->h)};
		SDL_FRect dstRect_deltaTime = {10.0f, 30.0f, static_cast<float>(surface_deltaTime->w), static_cast<float>(surface_deltaTime->h)};
		SDL_FRect dstRect_speed = {10.0f, 50.0f, static_cast<float>(surface_speed->w), static_cast<float>(surface_speed->h)};

		SDL_RenderTexture(renderer, texture_fps, nullptr, &dstRect_fps);
		SDL_RenderTexture(renderer, texture_deltaTime, nullptr, &dstRect_deltaTime);
		SDL_RenderTexture(renderer, texture_speed, nullptr, &dstRect_speed);

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