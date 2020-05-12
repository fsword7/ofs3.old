/*
 * shader.cpp - GLSL program package for OpenGL
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/context.h"
#include "render/gl/shader.h"


ShaderSource::ShaderSource(ShaderType type)
: type(type)
{
	GLenum idType;

	switch (type)
	{
	case shrVertexProcessor:
		idType = GL_VERTEX_SHADER;
		break;
	case shrFragmentProcessor:
		idType = GL_FRAGMENT_SHADER;
		break;
	}

	id = glCreateShader(idType);
}

ShaderSource::~ShaderSource()
{
	glDeleteShader(id);
}

void ShaderSource::dump(ostream &out, const string &source)
{
	bool newLine = true;
	int lineNumber = 0;

	for (int idx = 0; idx < source.length(); idx++) {
		if (newLine == true) {
			lineNumber++;
			out << fmt::sprintf("%04d: ", lineNumber);
			newLine = false;
		}

		out << source[idx];
		if (source[idx] == '\n')
			newLine = true;
	}
	out << endl;

	out.flush();
}
