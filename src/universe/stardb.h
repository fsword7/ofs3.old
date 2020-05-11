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

		bool loadXHIPData(fs::path dataFolder);

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
