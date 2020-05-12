/*
 * scene.h - scene renderer package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/gl/context.h"

namespace ofs::renderer
{
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		void init();
		void render();

	private:
//		void buildGaussDiscStar(uint32_t log2Size, double scale, double base);
		void buildGaussGlareStar(uint32_t log2Size, double scale, double base);

	private:
		Context gl;
	};
}
