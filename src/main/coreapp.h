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

		virtual void init();
		virtual void clean();
		virtual void update();

		virtual void initScreen() = 0;
		virtual void closeScreen() = 0;

	private:
		Engine *engine = nullptr;
	};
}
