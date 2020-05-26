/*
 * universe.h - Universe package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "universe/object.h"
#include "universe/stardb.h"
#include "universe/asterisms.h"

namespace ofs::universe
{
	class Universe
	{
	public:
		Universe() = default;
		~Universe() = default;

		inline const StarCatalog &getStarCatalog() const { return starlib; }
		inline const Asterism &getAsterism() const { return asterism; }

		void init();

		void findCloseStars(const vec3d_t& obs, double mdist,
				vector<const CelestialStar *>& stars) const;

	private:
		StarCatalog starlib;
		Asterism    asterism;
	};
}
