/*
 * universe.cpp - Universe package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "universe/astro.h"
#include "universe/universe.h"
#include "render/scene.h"

using namespace ofs::astro;
using namespace ofs::universe;
using namespace ofs::renderer;

void Universe::init()
{
	fs::path cwd = fs::current_path();
//	cerr << "Current directory: " << fs::current_path() << std::endl;

	starlib.loadXHIPData(cwd / "data");

	asterism.load(cwd / "data/asterisms/western/constellationship.fab");
//	asterism.load(cwd / "data/asterisms/western_rey/constellationship.fab");
}

Object *Universe::find(const string &name) const
{
	return starlib.find(name);
}

void Universe::findCloseStars(const vec3d_t& obs, double mdist,
		vector<const CelestialStar *>& stars) const
{
	int count;

	starlib.findCloseStars(obs / KM_PER_PC, mdist /* * LY_PER_PARSEC */, stars);

//	fmt::fprintf(cout, "Found %d closest stars\n", stars.size());
//	for (int idx = 0; idx < stars.size(); idx++)
//		fmt::fprintf(cout, "Star name: %s\n", stars[idx]->getName());
}
