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

	void setVertices(int nVertices, vec3d_t *vertices);
	void setIndices(int nIndices, uint16_t *indices);

private:
	int       nVertices = 0;
	int       nIndices = 0;
	vec3d_t  *vertices = nullptr;
	uint16_t *indices = nullptr;
};
