/*
 * mesh.h - mesh package for OpenGL
 *
 *  Created on: May 28, 2020
 *      Author: Tim Stark
 */

#pragma once

class Mesh
{
public:
	Mesh();
	~Mesh();

private:
	int       nVertices = 0;
	int       nIndices = 0;
	vec3d_t  *vertices = nullptr;
	uint16_t *indices = nullptr;
};
