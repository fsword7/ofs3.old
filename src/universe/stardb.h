/*
 * stardb.h - Star catalog database package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "universe/xhipdata.h"
#include "universe/startree.h"

namespace ofs::universe
{
//	class CelestialStar;

	class StarCatalog
	{
	public:
		StarCatalog() = default;
		~StarCatalog() = default;

		inline CelestialStar *getIndex(int hip) const { return hipCatalogue[hip]; }

		bool loadXHIPData(fs::path dataFolder);

		void findVisibleStars(const ofsHandler& handle, const vec3d_t& obs,
				const quatd_t &rot, double fov, double aspect, double limitMag) const;
        void findCloseStars(const vec3d_t& obs, double radius,
        	vector<const CelestialStar *>& stars) const;

	private:
		void initOctreeData(vector<CelestialStar*> stars);
		void finish();

	private:
		vector<CelestialStar *> uStars;

    	// Star catalogues
    	CelestialStar **hipCatalogue = nullptr;

    	StarTree *starTree;
	};
}
