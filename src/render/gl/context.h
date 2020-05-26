/*
 * context.h - context package for OpenGL
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

#include <GL/glew.h>

class Context
{
public:
	Context() = default;
	~Context() = default;

	void init(uint32_t width, uint32_t height);

	void start();
	void finish();

	void setViewport(int width, int height);
	void enableBlend();
	void disableBlend();

private:
	uint32_t height = 1;
	uint32_t width  = 1;
	double   aspect = double(width)/double(height);

};
