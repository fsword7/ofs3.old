/*
 * main.cpp - SDL2-based main package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "main/core.h"
#include "main/sdl2/core.h"

void sdlCoreApp::initScreen()
{
	// SDL main initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cerr << "OFS: SDL2 Main Initialization failure: " << SDL_GetError() << endl;
		abort();
	}

	// SDL image initialization
	int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF;
	int rcFlags = IMG_Init(imgFlags);
	if ((imgFlags & rcFlags) != imgFlags)
	{
		cerr << "OFS: SDL2 Image Initialization Failure: " << IMG_GetError() << endl;
		abort();
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// OpenGL window/full screen
	dWindow = SDL_CreateWindow(OFS_FULL_NAME,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			OFS_DEFAULT_WIDTH, OFS_DEFAULT_HEIGHT,
			SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	if (dWindow == nullptr) {
		cerr << "SDL2 Window can't be created: " << SDL_GetError() << endl;
		exit(1);
	}
	auto ctx = SDL_GL_CreateContext(dWindow);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		cerr << "GLEW Error: " << glewGetErrorString(err) << endl;
		exit(1);
	} else {
		cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << endl;
		cout << "  OpenGL version:   " << glGetString(GL_VERSION) << endl;
	}

	cout << "Everything good!" << endl;
}

void sdlCoreApp::closeScreen()
{
	SDL_DestroyWindow(dWindow);

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char **argv)
{
	using namespace ofs::engine;

	sdlCoreApp app;

	bool running = true;

	cout << "Orbital Flight Simulator" << endl;

	app.initScreen();
	app.init();

	while (running)
	{
		SDL_Event event;

		while(SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}

		app.update();
	}

	app.clean();

	return 0;
}
