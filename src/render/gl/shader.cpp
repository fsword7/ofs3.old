/*
 * shader.cpp - GLSL program package for OpenGL
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/context.h"
#include "render/gl/shader.h"

static ShaderList shaderList[2] =
{
		{ "vs", "Vertex",   shrVertexProcessor   },
		{ "fs", "Fragment", shrFragmentProcessor },
};

ShaderSource::ShaderSource(ShaderList *info)
: info(info), type(info->type)
{
	GLenum idType;

	switch (info->type)
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
	sources.clear();
	glDeleteShader(id);
}

void ShaderSource::dump(ostream &out, const string &fname, const string &source)
{
	bool newLine = true;
	int lineNumber = 0;

	fmt::fprintf(out, "OFS: File '%s' - %s processor\n", fname, info->desc);

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

const string ShaderSource::getLogInfo()
{
	GLint   lsize = 0;
	GLsizei size  = 0;

	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lsize);
	if (lsize <= 0)
		return string();

	char *clog = new char[lsize];
	if (clog == nullptr)
		return string();

	glGetShaderInfoLog(id, lsize, &size, clog);
	string slog(clog, size);
	delete [] clog;

	return slog;
}

ShaderStatus ShaderSource::compile(const vector<string> &source)
{
	GLint status;

	if (source.empty())
		return ShaderStatus::shrEmptyProgram;

	const char **src = new const char*[source.size()];
	for (unsigned int idx = 0; idx < source.size(); idx++) {
		sources.push_back(source[idx]);
		src[idx] = source[idx].c_str();
	}

	glShaderSource(id, source.size(), src, nullptr);
	delete [] src;

	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
		return ShaderStatus::shrCompileError;
	return ShaderStatus::shrSuccessful;
}

ShaderSource *ShaderSource::create(const string &processName)
{
	for (int idx = 0; idx < sizeof(shaderList); idx++)
		if (shaderList[idx].name == processName)
			return new ShaderSource(&shaderList[idx]);
	return nullptr;
}

// ******** Shader Program ********

ShaderProgram::ShaderProgram(const string &name)
: name(name)
{
	id = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	// Delete all old shader sources
	for (int idx = 0; idx < shaders.size(); idx++)
		delete shaders[idx];
	shaders.clear();

	// All done, delete program id
	glDeleteProgram(id);
}

void ShaderProgram::attach(const ShaderSource *shader)
{
	shaders.push_back(shader);
	glAttachShader(id, shader->getID());
}

const string ShaderProgram::getLogInfo()
{
	GLint   lsize = 0;
	GLsizei size  = 0;

	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &lsize);
	if (lsize <= 0)
		return string();

	char *clog = new char[lsize];
	if (clog == nullptr)
		return string();

	glGetProgramInfoLog(id, lsize, &size, clog);
	string slog(clog, size);
	delete [] clog;

	return slog;
}

ShaderStatus ShaderProgram::link(ostream &out)
{
	GLint  status;
	string log;

	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		log = getLogInfo();
		out << "\nLinking shader program error:\n" << endl;
		out << log << endl;
		out.flush();

		return ShaderStatus::shrLinkError;
	}

	return ShaderStatus::shrSuccessful;
}

//void ShaderProgram::setLightParameters(const LightState *ls,
//	Color diffuse, Color specular, Color emissive)
//{
//
//	int nLights = ls->nLights;
//
//	for (int idx = 0; idx < nLights; idx++) {
//		const DirectLight &light = ls->lights[idx];
//
//		vec3f_t color = vec3f_t(light.color.getRed(),
//								light.color.getGreen(),
//								light.color.getBlue()) * float(light.irradiance);
//
//		lights[idx].direction = light.directObject;
//		lights[idx].diffuse = color;
//		lights[idx].specular = color;
//	}
//}

// ******** Shader Manager ********

ShaderProgram *ShaderManager::buildPrograms(const string &name)
{

	fs::path shaderFolder = fs::current_path() / "shaders";
	ShaderProgram *pgm = new ShaderProgram(name);
	ShaderStatus status;

	for (const auto &p : fs::directory_iterator(shaderFolder)) {
		fs::path sfile = p.path();
		const string pgmFile = sfile.filename().string();
		const string fname = sfile.stem().string();

		string::size_type sep = fname.find('-', 0);
		if (sep == string::npos)
			continue;

		string pgmName = string(fname, 0, sep);
		string pgmType = string(fname, sep+1, fname.size());
		if (pgmName != name)
			continue;

//		cout << fmt::sprintf("File: %s => Name: %s Type: %s\n",
//			pgmFile, pgmName, pgmType);

		ifstream srcFile(sfile);
		string pgmSource;
		if (srcFile.good())
		{
			auto srcSize = p.file_size();

			pgmSource = string(srcSize, '\0');
			srcFile.read(&pgmSource[0], srcSize);
			srcFile.close();

			cout << pgmSource << "\nSize: " << pgmSource.size() << endl;

			ShaderSource *shader = ShaderSource::create(pgmType);
			if (shader != nullptr) {
				vector<string> sourcev;
				string log;

				cout << "File length: " << srcSize << endl;
				shader->dump(cout, pgmFile, pgmSource);

				sourcev.push_back(pgmSource);
				status = shader->compile(sourcev);
				if (status != ShaderStatus::shrSuccessful) {
					if (status == ShaderStatus::shrEmptyProgram)
						cout << "\nOFS: Empty program - not compiled.\n" << endl;
					else {
						log = shader->getLogInfo();
						cout << "\nCompiling shader source error:\n" << endl;
						cout << log << endl;
						cout.flush();

						delete shader;
						return nullptr;
					}
				}

				// All done, attach shader to program for linking later
				pgm->attach(shader);

			} else {
				fmt::fprintf(cerr, "OFS: Shader %s: Unknown processor type: %s\n",
					pgmName, pgmType);
			}
		} else {
			fmt::fprintf(cerr, "OFS: Failed to open '%s' file: %s\n",
				pgmFile, strerror(errno));
			delete pgm;
			return nullptr;
		}

	}

	status = pgm->link(cout);
	cout.flush();

	if (status != ShaderStatus::shrSuccessful) {
		delete pgm;
		return nullptr;
	}

	return pgm;
}

ShaderProgram *ShaderManager::getShader(const string &name)
{
	// Check existing shader programs first.
	for (int idx = 0; idx < programs.size(); idx++)
		if (programs[idx]->getName() == name)
			return programs[idx];

	fs::path shaderFolder = fs::current_path() / "shaders";
	fs::path vsName = fmt::sprintf("%s-vs.glsl", name);
	fs::path fsName = fmt::sprintf("%s-fs.glsl", name);

	string vsSource, fsSource;
	struct stat st;

	ShaderProgram *pgm = buildPrograms(name);
	if (pgm == nullptr)
		return nullptr;
	programs.push_back(pgm);

	return pgm;
}
