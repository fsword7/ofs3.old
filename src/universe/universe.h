/*
 * universe.h - Universe package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "universe/object.h"
#include "universe/stardb.h"

namespace ofs::universe
{
	class Universe
	{
	public:
		Universe() = default;
		~Universe() = default;

		void init();

		void findCloseStars(const vec3d_t& obs, double mdist,
				vector<const CelestialStar *>& stars) const;

	private:
		StarCatalog starlib;
	};
}
