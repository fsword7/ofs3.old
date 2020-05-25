/*
 * context.cpp - Context package for OpenGL
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/context.h"

void Context::start()
{
	// Clear all screen
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

}

void Context::finish()
{

}

void Context::enableBlend()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void Context::disableBlend()
{
	glDisable(GL_BLEND);
}
