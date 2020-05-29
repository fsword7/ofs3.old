/*
 * mesh.cpp - mesh package for OpenGL
 *
 *  Created on: May 28, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/context.h"
#include "render/gl/mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	if (vertices != nullptr)
		delete [] vertices;
	if (indices != nullptr)
		delete [] indices;
}
