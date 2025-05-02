#include <SDL3/SDL.h>
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS; // in ms

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

	SDL_Surface *surface = SDL_LoadBMP("sample.bmp");
	SDL_Texture *boxTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	// * Main game loop
	bool isRunning = true;
	SDL_Event event;

	float angle = 0.0f;

	// * Event tick
	Uint32 lastTime = SDL_GetTicks(); // milisecond

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

		angle += 90 * deltaTime; // * rotate 90° per second
		std::cout << "angle: " << angle << std::endl;

		// * Render
		SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
		SDL_RenderClear(renderer);

		// * Draw filled rect (player)
		SDL_FRect playerRect = {100, 100, 100, 100};
		SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);
		SDL_RenderFillRect(renderer, &playerRect);

		// * Draw a line (laser or direction)
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderLine(renderer, 150, 150, 400, 400);

		// * Rotating rectangle
		SDL_FRect rotatingRect = {400, 250, 80, 80};
		SDL_SetRenderDrawColor(renderer, 0, 120, 255, 200);

		SDL_Vertex verts[4];
		int indices[6] = {0, 1, 2, 2, 3, 0};

		float cx = rotatingRect.x + rotatingRect.w / 2;
		float cy = rotatingRect.y + rotatingRect.h / 2;

		float x0 = rotatingRect.x;
		float y0 = rotatingRect.y;

		float x1 = rotatingRect.x + rotatingRect.w;
		float y1 = rotatingRect.y;

		float x2 = rotatingRect.x + rotatingRect.w;
		float y2 = rotatingRect.y + rotatingRect.h;

		float x3 = rotatingRect.x;
		float y3 = rotatingRect.y + rotatingRect.h;

		auto rotatePoint = [=](float &x, float &y)
		{
			float rad = angle * (M_PI / 180.0f);
			float s = sin(rad);
			float c = cos(rad);

			x -= cx;
			y -= cy;
			float xnew = x * c - y * s;
			float ynew = x * s + y * c;
			x = xnew + cx;
			y = ynew + cy;
		};

		rotatePoint(x0, y0);
		rotatePoint(x1, y1);
		rotatePoint(x2, y2);
		rotatePoint(x3, y3);

		SDL_Color color = {0, 120, 255, 200};

		// Convert SDL_Color to SDL_FColor
		SDL_FColor fcolor = {
				color.r / 255.0f,
				color.g / 255.0f,
				color.b / 255.0f,
				color.a / 255.0f
			};

		verts[0].position = {x0, y0};
		verts[1].position = {x1, y1};
		verts[2].position = {x2, y2};
		verts[3].position = {x3, y3};
		for (int i = 0; i < 4; i++)
		{
			verts[i].color = fcolor;
			verts[i].tex_coord = {0, 0};
		}

		SDL_RenderGeometry(renderer, nullptr, verts, 4, indices, 6); // * placeholder

		// SDL_RenderTextureRotated(renderer, boxTexture, nullptr, &rotatingRect, angle, nullptr, SDL_FLIP_NONE); // ! if using this texture

		SDL_RenderPresent(renderer);

		// SDL_Delay(16);  // ! ~60 FPS
	}

	// * Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}