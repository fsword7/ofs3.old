/*
 * stars.h - star renderer package
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/gl/context.h"
#include "render/gl/buffer.h"
#include "render/gl/shader.h"
#include "render/gl/stars.h"

namespace ofs::renderer
{
	class StarRenderer
	{
	public:
		StarRenderer() = default;
		~StarRenderer() = default;

	public:
		Context *ctx = nullptr;
		ShaderProgram *pgm = nullptr;
		VertexBuffer *vbuf = nullptr;

		StarVertex *pointStarBuffer = nullptr;
		StarVertex *glareStarBuffer = nullptr;
	};
}
