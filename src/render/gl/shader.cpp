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

// ******** Shader Manager ********

ShaderProgram *ShaderManager::createShader(const string &name)
{
	// Check existing shader programs first.
	for (int idx = 0; idx < programs.size(); idx++)
		if (programs[idx]->getName() == name)
			return programs[idx];

	fs::path dataFolder = fs::current_path() / "data/shaders";
	fs::path vsName = fmt::sprintf("%s-vs.glsl", name);
	fs::path fsName = fmt::sprintf("%s-fs.glsl", name);

	string vsSource, fsSource;
	struct stat st;

	ifstream vsFile(dataFolder / vsName);
	if (vsFile.good())
	{
		auto vsSize = fs::file_size(vsName);

		vsSource = string(vsSize, '\0');
		vsFile.read(&vsSource[0], vsSize);
		vsFile.close();
	} else {
		fmt::print(cerr, "OFS: Failed to open '%s' file: %s\n",
			vsName, strerror(errno));
		return nullptr;
	}

	ifstream fsFile(dataFolder / fsName);
	if (fsFile.good())
	{
		auto fsSize = fs::file_size(fsName);

		fsSource = string(fsSize, '\0');
		fsFile.read(&fsSource[0], fsSize);
		fsFile.close();
	} else {
		fmt::print(cerr, "OFS: Failed to open '%s' file: %s\n",
			vsName, strerror(errno));
		return nullptr;
	}

	return nullptr;
}
