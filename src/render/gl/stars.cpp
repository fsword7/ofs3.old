/*
 * stars.cpp
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/context.h"
#include "render/gl/shader.h"
#include "render/gl/stars.h"
#include "render/scene.h"

using namespace ofs::renderer;

StarVertex::StarVertex(Scene *scene)
: scene(scene),
  ctx(scene->getContext()),
//  prm(*scene.getParameter()),
  type(useNotUsed),
  nStars(0),
  flagStarted(false)
{
}

StarVertex::~StarVertex()
{
}

//void StarVertex::setTexture(Texture *image)
//{
//	txImage = image;
//}

void StarVertex::init(StarRenderer *render)
{
	pgm  = render->pgm;
	vbuf = render->vbuf;
}

void StarVertex::start()
{
	pgm->use();
	vbuf->bind();

//	cout << "starVertex size: " << sizeof(starVertex) << endl;
//	cout << "  vec3f_t size:  " << sizeof(vec3f_t) << endl;
//	cout << "  Color size:    " << sizeof(Color) << endl;

	glBindBuffer(GL_ARRAY_BUFFER, vbuf->getVBO());
	glBufferData(GL_ARRAY_BUFFER, 120000 * sizeof(starVertex), nullptr, GL_STREAM_DRAW);
	vertices = reinterpret_cast<starVertex *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	if (vertices == nullptr) {
		cerr << "Can't render stars - aborted (error code: " << glGetError() << ")" << endl;
		return;
	}

	glEnable(GL_PROGRAM_POINT_SIZE);

//	mat4f_t mvp = mat4f_t (prm.dmProj * prm.dmView * mat4d_t(1.0));
//
//	uint32_t mvpLoc = glGetUniformLocation(pgm->getID(), "mvp");
//    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	nStars = 0;
	type = useSprites;
	flagStarted = true;
}

void StarVertex::render()
{
	if (!glUnmapBuffer(GL_ARRAY_BUFFER)) {
		cerr << "Buffer corrupted - aborted (error code: " << glGetError() << ")" << endl;
		return;
	}
	vertices = nullptr;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(starVertex), (void *)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(starVertex), (void *)(3 * sizeof(float)));
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(starVertex), (void *)(7 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Now rendering stars
//	if (txImage != nullptr)
//		txImage->bind();
	glDrawArrays(GL_POINTS, 0, nStars);
	nStars  = 0;
}

void StarVertex::finish()
{

	render();

	flagStarted = false;

//	cout << "Total " << cStars << " rendered stars." << endl;

	switch (type) {
	case useSprites:
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		vbuf->unbind();

		glUseProgram(0);
		glDisable(GL_PROGRAM_POINT_SIZE);
		break;
	case usePoints:
	default:
		break;
	}
	type = useNotUsed;
}

void StarVertex::addStar(const vec3d_t &pos, const Color &color, double size)
{
	vertices[nStars].posStar = pos;
	vertices[nStars].color = color;
	vertices[nStars].size = size;

	nStars++;
}

