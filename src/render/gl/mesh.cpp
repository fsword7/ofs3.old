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
	if (vbuf != nullptr)
		delete vbuf;
	if (vertices != nullptr)
		delete [] vertices;
	if (indices != nullptr)
		delete [] indices;
}

void Mesh::setVertices(int nVertices, vtxf_t *vertices)
{
	this->nVertices = nVertices;
	this->vertices = vertices;
}

void Mesh::setIndices(int nIndices, uint16_t *indices)
{
	this->nIndices = nIndices;
	this->indices = indices;
}

void Mesh::allocate(Context &gl)
{
    vbuf = new VertexBuffer(gl, 1);

   	vbuf->createBuffer(VertexBuffer::VBO, 1);
	vbuf->createBuffer(VertexBuffer::EBO, 1);

    allocatedFlag = true;
}

void Mesh::render(Context &gl)
{
	if (allocatedFlag == false)
		allocate(gl);
    vbuf->bind();

	vbuf->assign(VertexBuffer::VBO, vertices, nVertices*sizeof(vtxf_t));
    vbuf->assign(VertexBuffer::EBO, indices, nIndices*sizeof(uint16_t));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vtxf_t), (void *)0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vtxf_t), (void *)(3 * sizeof(float)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vtxf_t), (void *)(6 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vtxf_t), (void *)(9 * sizeof(float)));
	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_SHORT, 0);

	glDisable(GL_CULL_FACE);

	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	vbuf->unbind();
}
