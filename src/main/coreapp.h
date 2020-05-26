/*
 * coreapp.h - core application package
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "engine/engine.h"

using namespace ofs::engine;

namespace ofs
{
	class CoreApp
	{
	public:
		CoreApp() = default;
		virtual ~CoreApp() = default;

		void initEngine();

		virtual void init();
		virtual void clean();
		virtual void update();
		virtual void render();
		virtual void resize(int width, int height);

		virtual void initScreen() = 0;
		virtual void closeScreen() = 0;
		virtual void run() = 0;

	private:
		Engine *engine = nullptr;
	};
}
