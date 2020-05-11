/*
 * stardb.h - Star catalog database package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

namespace ofs::universe
{
//	class CelestialStar;

	class StarCatalog
	{
		StarCatalog() = default;
		~StarCatalog() = default;

	private:
		vector<CelestialStar *> stars;
	};
}
