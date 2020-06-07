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
	shrUnknownType,
	shrCompileError,
	shrLinkError,
	shrOutOfMemory,
	shrEmptyProgram
};

struct ShaderList
{
	const string name;
	const string desc;
	ShaderType   type;
};

class ShaderSource
{
public:
	ShaderSource(ShaderList *info);
	~ShaderSource();

	inline ShaderList *getInfo() const { return info; }
	inline uint32_t getID() const { return id; }

	void dump(ostream &out, const string &fname, const string &source);
	const string getLogInfo();

	ShaderStatus compile(const vector<string> &source);

	static ShaderSource *create(const string &type);

private:
	ShaderType type = shrUnknown;
	ShaderList *info = nullptr;
	GLuint id = 0;

	vector<string> sources;
};

class ShaderProgram
{
public:
	ShaderProgram(const string &name);
	~ShaderProgram();

	inline const string getName() const { return name; }
	inline int getID() const { return id; }
	inline void use() const { glUseProgram(id); }
	inline void release() const { glUseProgram(0); }

	void attach(const ShaderSource *shader);

	const string getLogInfo();
	ShaderStatus link(ostream &out);

//	void setLightParameters(const LightState *ls, Color diffuse, Color specular, Color emissive);

	void setColor(const string &name, Color color)
	{
		glUniform4f(glGetUniformLocation(id, name.c_str()),
			color.red, color.green, color.blue, color.alpha);
	}

	void setMatrix4fv(const string &name, mat4f_t &value)
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()),
			1, GL_FALSE, glm::value_ptr(value));
//		uint32_t loc = glGetUniformLocation(id, name.c_str());
//		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
	}

private:
	string name;
	GLuint id = 0;

	vector<const ShaderSource *> shaders;

	vec3f_t ambientColor;
	struct ShaderLight {
		vec3f_t direction;
		vec3f_t diffuse;
		vec3f_t specular;
	} lights[8];
};

class Context;
class ShaderManager
{
public:
	ShaderManager(Context &ctx)
	: gl(ctx)
	{}

	ShaderProgram *getShader(const string &name);

private:
	ShaderProgram *buildPrograms(const string &name);

private:
	Context &gl;

	vector<ShaderProgram *> programs;
};
