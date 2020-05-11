/*
 * main.cpp - SDL2-based main package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "main/core.h"

void init()
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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

//	// OpenGL window/full screen
//	dWindow = SDL_CreateWindow(APP_FULL_NAME,
//			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//			OFS_DEFAULT_WIDTH, OFS_DEFAULT_HEIGHT,
//			SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
//	if (dWindow == nullptr) {
//		cerr << "SDL2 Window can't be created: " << SDL_GetError() << endl;
//		exit(1);
//	}
//	auto ctx = SDL_GL_CreateContext(dWindow);
//
//
//	GLenum err = glewInit();
//	if (err != GLEW_OK) {
//		cerr << "GLEW Error: " << glewGetErrorString(err) << endl;
//		exit(1);
//	} else {
//		cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << endl;
//		cout << "  OpenGL version:   " << glGetString(GL_VERSION) << endl;
//	}

	cout << "Everything good!" << endl;
}

void clean()
{
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char **argv)
{
	cout << "Orbital Flight Simulator" << endl;

	init();
	clean();

	return 0;
}




