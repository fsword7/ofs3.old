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

		void render();

	private:
		Context gl;
	};
}
