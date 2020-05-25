/*
 * engine.h - Simulation engine package
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/scene.h"
#include "universe/universe.h"

using namespace ofs::renderer;
using namespace ofs::universe;

namespace ofs::engine
{
	class Engine
	{
	public:
		Engine() = default;
		~Engine() = default;

		void init();
		void render();

	private:
		Universe *universe = nullptr;
		Scene *scene = nullptr;
	};
}
