#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "KeyPressSurfaces.h"
#include <string>

using namespace std;

class TestOgre
{

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	// Loads individual image as texture
	SDL_Texture* loadTexture(string path);

	// The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	// The window renderer
	SDL_Renderer* gRenderer = NULL;

	// Current displayed texture
	SDL_Texture* gTexture = NULL;

	// The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	// The image we will load and show on the screen
	SDL_Surface* image1 = NULL;

public:
	TestOgre();
	~TestOgre();

	// Starts up SDL and creates window
	bool SDL_init();

	// Loads media
	bool loadMedia();

	// Frees media and shuts down SDL
	void close();

	// Loads individual image
	SDL_Surface* loadSurface(string path);

	// The images that correspondto a keypress
	SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

	// Current displayed image
	SDL_Surface* gCurrentSurface = NULL;

	void handleKeyPress(SDL_Keycode key);

	// Begins the main game process
	int run();
};

