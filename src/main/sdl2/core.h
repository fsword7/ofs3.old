/*
 * core.h - core application package for SDL 2.x interface
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "main/coreapp.h"

class sdlCoreApp : public ofs::CoreApp
{
public:
	sdlCoreApp() = default;
	~sdlCoreApp() = default;

	void initScreen() override;
	void closeScreen() override;

private:
	SDL_Window *dWindow = nullptr;
};
