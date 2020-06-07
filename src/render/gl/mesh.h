/*
 * mesh.h - mesh package for OpenGL
 *
 *  Created on: May 28, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/gl/buffer.h"

template <typename T>
struct Vertex {
	T vx, vy, vz;
	T nx, ny, nz;
	T tu, tv;
};

template <typename T>
struct tcRange
{
	T tumin, tumax;
	T tvmin, tvmax;
};

typedef Vertex<float> vtxf_t;
typedef Vertex<double> vtxd_t;
typedef tcRange<float> tcrf_t;
typedef tcRange<double> tcrd_t;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void setVertices(int nVertices, vtxf_t *vertices);
	void setIndices(int nIndices, uint16_t *indices);

	void allocate(Context &gl);
	void render(Context &gl);

private:
	int       nVertices = 0;
	int       nIndices = 0;
	vtxf_t   *vertices = nullptr;
	uint16_t *indices = nullptr;

	bool allocatedFlag = false;
	VertexBuffer *vbuf = nullptr;
};
