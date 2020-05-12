/*
 * universe.cpp - Universe package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "universe/universe.h"
#include "render/scene.h"

using namespace ofs::universe;
using namespace ofs::renderer;

void Universe::init()
{
	fs::path cwd = fs::current_path();
//	cerr << "Current directory: " << fs::current_path() << std::endl;

	starlib.loadXHIPData(cwd / "data");


	Scene *scene = new Scene();
	scene->init();
}
