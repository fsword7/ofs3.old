/*
 * engine.cpp - Simulation engine package
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/engine.h"

using namespace ofs::engine;
using namespace ofs::universe;

void Engine::init()
{
	player = new Player();
	universe = new Universe();
	scene = new Scene();

	universe->init();
	scene->init(OFS_DEFAULT_WIDTH, OFS_DEFAULT_HEIGHT);
}

void Engine::render()
{
	scene->render(player, universe);
}
