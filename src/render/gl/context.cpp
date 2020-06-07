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
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

}

void Context::finish()
{

}

void Context::setColor(Color color)
{
	glColor4f(color.red, color.green, color.blue, color.alpha);
}

void Context::setViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void Context::setPolygonMode(PolygonMode mode)
{
	switch (mode)
	{
	case modeWireframe:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;

	case modeFill:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
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
