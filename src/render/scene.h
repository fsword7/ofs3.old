/*
 * scene.h - scene renderer package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/gl/context.h"
#include "render/gl/shader.h"

namespace ofs::renderer
{
	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		void init();
		void render();

	private:
//		void buildGaussDiscStar(uint32_t log2Size, double scale, double base);
		uint16_t *buildGaussGlareStar(uint32_t log2Size, double scale, double base);

	private:
		Context gl;

		ShaderManager smgr;
	};
}
