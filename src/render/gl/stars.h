/*
 * stars.h - star renderer for OpenGL
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/renderprm.h"

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

	StarVertex(Context &gl);
	~StarVertex();

//	void init();

	// Render routines
	void start(const RenderParameter &prm);
	void render();
	void finish();

	void addStar(const vec3d_t &pos, const Color &color, double size);
//	void setTexture(Texture *image);

protected:
	Context &gl;
//	renderParameter &prm;

	pointType type = useNotUsed;
	int  nStars = 0;
	bool flagStarted = false;

	ShaderProgram *pgmStar = nullptr;
	VertexBuffer  *vbufStar = nullptr;

//	Texture *txImage = nullptr;

    starVertex *vertices = nullptr;
};
