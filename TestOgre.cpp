#include "TestOgre.h"

TestOgre::TestOgre()
{
	if (!SDL_init())
	{
		printf("Failed to initialize!\n");
	}
}

bool TestOgre::SDL_init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("WIndow could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			// TODO 
			//gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			// Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SLD_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				// Get window surface
				screenSurface = SDL_GetWindowSurface(gWindow);
			}

			//// Fill the surface white
			//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//// Update the surface
			//SDL_UpdateWindowSurface(window);

			// Load media
			if (!loadMedia())
			{
				printf("Failed to load media!\n");
			}
			else
			{


				image1 = loadSurface("images/loaded.png");

				// Apply the image
				SDL_BlitSurface(image1, NULL, screenSurface, NULL);

				// Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	return success;
}

bool TestOgre::loadMedia()
{
	// Loading success flag
	bool success = true;

	    //Load default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "04_key_presses/press.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "04_key_presses/up.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "04_key_presses/down.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "04_key_presses/left.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "04_key_presses/right.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

	// Load splash image
	//image1 = SDL_LoadBMP("images/preview.bmp");
	//if (image1 == NULL)
	//{
	//	printf("Unable to load image %s! SDL Error: %s\n", "images/preview.bmp", SDL_GetError());
	//	success = false;
	//}

	return success;
}

SDL_Surface* TestOgre::loadSurface(string path)
{
	// The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	// Load image at specified path
	//SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface,screenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

int TestOgre::run()
{
	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

	// Set default current surface
	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

	// While application is running
	while (!quit)
	{
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			// User presses a key
			else if (e.type == SDL_KEYDOWN) {
				handleKeyPress(e.key.keysym.sym);
			}

		}
	}

	//// Wait two seconds
	//SDL_Delay(5000);

	return 0;
}

void TestOgre::handleKeyPress(SDL_Keycode key) {
	switch (key) {
		case SDLK_UP:
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
			break;
		case SDLK_DOWN:
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
			break;
		case SDLK_LEFT:
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
			break;
		case SDLK_RIGHT:
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
			break;
		default:
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			break;
	}

	// Apply the current image
	//SDL_BlitSurface(gCurrentSurface, NULL, screenSurface, NULL);

	// Apply the image stretched
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	SDL_BlitScaled(gCurrentSurface, NULL, screenSurface, &stretchRect);

	// Update the surface
	SDL_UpdateWindowSurface(gWindow);
}

void TestOgre::close()
{
	// Deallocate surface
	SDL_FreeSurface(image1);
	image1 = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

TestOgre::~TestOgre()
{
	close();
}
