/*
 * engine.h - Simulation engine package
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "engine/player.h"
#include "universe/universe.h"
#include "render/scene.h"

namespace ofs::engine
{
	using Scene = ofs::renderer::Scene;
	using Universe = ofs::universe::Universe;

	class Engine
	{
	public:
		Engine() = default;
		~Engine() = default;

		inline Player *getPlayer() const { return player; }
		inline Scene *getScene() const { return scene; }
		inline Universe *getUniverse() const { return universe; }

		void init();
		void resize(int width, int height);
		void update(double dt);
		void render();

	private:
		Player *player = nullptr;
		Universe *universe = nullptr;
		Scene *scene = nullptr;
	};
}
