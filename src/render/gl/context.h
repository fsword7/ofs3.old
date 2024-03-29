/*
 * context.h - context package for OpenGL
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

#include <GL/glew.h>

#include "render/gl/shader.h"

class Context
{
public:
	enum PolygonMode
	{
		modeWireframe,
		modeFill
	};

	Context() : smgr(*this) {}
	~Context() = default;

	inline uint32_t getWidth() const { return width; }
	inline uint32_t getHeight() const { return height; }

	void init(uint32_t width, uint32_t height);

	void start();
	void finish();

	void setViewport(int width, int height);
	void setPolygonMode(PolygonMode mode);
	void enableBlend();
	void disableBlend();

	inline ShaderProgram *getShader(const string &name) { return smgr.getShader(name); }

private:
	uint32_t height = 1;
	uint32_t width  = 1;
	double   aspect = double(width)/double(height);

	ShaderManager smgr;
};
