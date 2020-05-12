/*
 * shader.h - GLSL program package for OpenGL
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/gl/context.h"

enum ShaderType
{
	shrUnknown = 0,
	shrVertexProcessor,
	shrFragmentProcessor
};

enum ShaderStatus
{
	shrSuccessful = 0,
	shrCompileError,
	shrLinkError,
	shrOutOfMemory,
	shrEmptyProgram
};

class ShaderSource
{
public:
	ShaderSource(ShaderType type);
	~ShaderSource();

	inline uint32_t getID() const { return id; }

	void dump(ostream &out, const string &source);

private:
	ShaderType type = shrUnknown;
	GLuint id = 0;
};

class ShaderProgram
{

};

class ShaderManager
{
public:
	ShaderManager(Context *ctx)
	: gl(ctx)
	{}

private:
	Context *gl;
};
