/*
 * main.cpp - SDL2-based main package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "main/core.h"
#include "main/sdl2/coreapp.h"

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

void sdlCoreApp::display(const string &title)
{
	SDL_SetWindowTitle(dWindow, title.c_str());
}

void sdlCoreApp::handleMouseWheelEvent(const SDL_MouseWheelEvent &event)
{
	if (event.y > 0)
		mouseDialWheel(-1.0);
	else if (event.y < 0)
		mouseDialWheel(1.0);
}

void sdlCoreApp::pressKeyEvent(SDL_KeyboardEvent *key, bool down)
{
//	using namespace ofs;

	CoreApp::keyCode code = keyUndefined;
	char32_t ch;
	uint16_t mod;

	mod = key->keysym.mod;

//	if (mod & KMOD_CTRL)
//		state |= mouseControlKey;
//	if (mod & KMOD_SHIFT)
//		state |= mouseShiftKey;

	switch(key->keysym.sym)
	{
    case SDLK_F1:		code = keyF1;		break;
    case SDLK_F2:		code = keyF2;		break;
    case SDLK_F3:		code = keyF3;		break;
    case SDLK_F4:		code = keyF4;		break;
    case SDLK_F5:		code = keyF5;		break;
    case SDLK_F6:		code = keyF6;		break;
    case SDLK_F7:		code = keyF7;		break;
    case SDLK_F8:		code = keyF8;		break;
    case SDLK_F9:		code = keyF9;		break;
    case SDLK_F10:		code = keyF10;		break;
    case SDLK_F11:		code = keyF11;		break;
    case SDLK_F12:		code = keyF12;		break;

	case SDLK_KP_0:		code = keyPad0;		break;
	case SDLK_KP_1:		code = keyPad1;		break;
	case SDLK_KP_2:		code = keyPad2;		break;
	case SDLK_KP_3:		code = keyPad3;		break;
	case SDLK_KP_4:		code = keyPad4;		break;
	case SDLK_KP_5:		code = keyPad5;		break;
	case SDLK_KP_6:		code = keyPad6;		break;
	case SDLK_KP_7:		code = keyPad7;		break;
	case SDLK_KP_8:		code = keyPad8;		break;
	case SDLK_KP_9:		code = keyPad9;		break;

	case SDLK_LEFT:		code = keyLeft;		break;
	case SDLK_RIGHT:	code = keyRight;	break;
	case SDLK_UP:		code = keyUp;		break;
	case SDLK_DOWN:		code = keyDown;		break;

	case SDLK_HOME:		code = keyHome;		break;
	case SDLK_END:		code = keyEnd;		break;

    default: // ASCII codes
    	ch = key->keysym.sym;
    	if ((down == false) || (ch & ~0xFF))
    		break;
    	keyEntered(ch, mod);
    	break;
	}

	if (code > 0)
		keyPress(code, mod, down);
}

void sdlCoreApp::run()
{
	bool  running = true;
	int   w, h;
	int   mx, my, lx, ly;
	float vx = 0.0f, vy = 0.0f;
	int   state;
	uint16_t mod;
	string title;

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

			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					SDL_GetWindowSize(dWindow, &w, &h);
					resize(w, h);
				}
				break;

			// Handling joystick events

			// Handling mouse events
			case SDL_MOUSEMOTION:
				mx = event.motion.x;
				my = event.motion.y;

				state = 0;
				if (event.motion.state & SDL_BUTTON_LMASK)
					state |= mouseLeftButton;
				if (event.motion.state & SDL_BUTTON_MMASK)
					state |= mouseMiddleButton;
				if (event.motion.state & SDL_BUTTON_RMASK)
					state |= mouseRightButton;
				if (mod & KMOD_CTRL)
					state |= keyControl;
				if (mod & KMOD_SHIFT)
					state |= keyShift;
				if (mod & KMOD_ALT)
					state |= keyAlternate;

//				if (views.size() > 0) {
//					view = views[0];
//					view->map(mx/float(width), my/float(height), vx, vy);
//				}

				title = fmt::sprintf("%s X: %d Y: %d (%f,%f) State: %c%c%c%c%c%c\n",
					OFS_FULL_NAME, mx, my, vx, vy,
					(state & mouseLeftButton   ? 'L' : '-'),
					(state & mouseMiddleButton ? 'M' : '-'),
					(state & mouseRightButton  ? 'R' : '-'),
					(state & keyControl        ? 'C' : '-'),
					(state & keyShift          ? 'S' : '-'),
					(state & keyAlternate      ? 'A' : '-'));
				display(title);

				mouseMove(mx, my, state);
				break;

			case SDL_MOUSEBUTTONDOWN:
				mx = event.motion.x;
				my = event.motion.y;

				state = 0;
				if (event.motion.state & SDL_BUTTON_LMASK)
					state |= mouseLeftButton;
				if (event.motion.state & SDL_BUTTON_MMASK)
					state |= mouseMiddleButton;
				if (event.motion.state & SDL_BUTTON_RMASK)
					state |= mouseRightButton;
				if (mod & KMOD_CTRL)
					state |= keyControl;
				if (mod & KMOD_SHIFT)
					state |= keyShift;
				if (mod & KMOD_ALT)
					state |= keyAlternate;

				mousePressButtonDown(mx, my, state);
				break;

			case SDL_MOUSEBUTTONUP:
				mx = event.motion.x;
				my = event.motion.y;

				state = 0;
				if (event.motion.state & SDL_BUTTON_LMASK)
					state |= mouseLeftButton;
				if (event.motion.state & SDL_BUTTON_MMASK)
					state |= mouseMiddleButton;
				if (event.motion.state & SDL_BUTTON_RMASK)
					state |= mouseRightButton;
				if (mod & KMOD_CTRL)
					state |= keyControl;
				if (mod & KMOD_SHIFT)
					state |= keyShift;
				if (mod & KMOD_ALT)
					state |= keyAlternate;

				mousePressButtonUp(mx, my, state);
				break;

			case SDL_MOUSEWHEEL:
				handleMouseWheelEvent(event.wheel);
				break;

			// Handling keyboard events
			case SDL_KEYDOWN:
				mod = event.key.keysym.mod;

//				state = 0;
//				if (mod & KMOD_CTRL)
//					state |= keyControl;
//				if (mod & KMOD_SHIFT)
//					state |= keyShift;
//				if (mod & KMOD_ALT)
//					state |= keyAlternate;

				pressKeyEvent(&event.key, true);

				break;

			case SDL_KEYUP:
				mod = event.key.keysym.mod;

//				state = 0;
//				if (mod & KMOD_CTRL)
//					state |= keyControl;
//				if (mod & KMOD_SHIFT)
//					state |= keyShift;
//				if (mod & KMOD_ALT)
//					state |= keyAlternate;

				pressKeyEvent(&event.key, false);
				break;
			}

		}

		update();
		render();
		SDL_GL_SwapWindow(dWindow);
	}
}

int main(int argc, char **argv)
{
	using namespace ofs::engine;

	sdlCoreApp app;

	bool running = true;

	cout << "Orbital Flight Simulator" << endl;

	app.init();
	app.initScreen();
	app.initEngine();

	app.run();

	app.clean();

	return 0;
}
