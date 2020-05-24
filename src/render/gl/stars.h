/*
 * stars.h - star renderer for OpenGL
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/scene.h"

using namespace ofs::renderer;

class StarVertex
{
public:
	enum pointType {
		useNotUsed = 0,
		usePoints,
		useSprites
	};

	struct starVertex
	{
		vec3f_t		posStar;
		Color		color;
		float		size;
	};

	StarVertex(Scene *scene);
	~StarVertex();

	void init(StarRenderer *render);

	// Render routines
	void start();
	void render();
	void finish();

	void addStar(const vec3d_t &pos, const Color &color, double size);
//	void setTexture(Texture *image);

protected:
	ofs::renderer::Scene *scene;
	Context &ctx;
//	renderParameter &prm;

	pointType type;
	int  nStars;
	bool flagStarted;

	ShaderProgram *pgm = nullptr;
	VertexBuffer  *vbuf = nullptr;

//	Texture *txImage = nullptr;

    starVertex *vertices = nullptr;
};
