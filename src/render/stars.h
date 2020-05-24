/*
 * stars.h - star renderer package
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/gl/context.h"
#include "render/gl/shader.h"

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
	};
}
