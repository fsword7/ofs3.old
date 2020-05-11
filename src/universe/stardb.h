/*
 * stardb.h - Star catalog database package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "universe/xhipdata.h"

namespace ofs::universe
{
//	class CelestialStar;

	class StarCatalog
	{
	public:
		StarCatalog() = default;
		~StarCatalog() = default;

		bool loadXHIPData(fs::path dataFolder);

	private:
		vector<CelestialStar *> uStars;
	};
}
