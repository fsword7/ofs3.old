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
	scene->init(*universe, OFS_DEFAULT_WIDTH, OFS_DEFAULT_HEIGHT);

	// Hacks - To be removed later
	Object *sun = universe->find("Sol");
	if (sun != nullptr) {
//		cout << "Star name: " << sun->getName() << endl << flush;
		player->move(*sun);
		player->look(*sun);
	} else
		cout << "Object 'Sol' not found" << endl << flush;
}

void Engine::resize(int width, int height)
{
	scene->resize(width, height);
}

void Engine::update(double dt)
{
	player->update(dt);
}

void Engine::render()
{
	scene->render(player, universe);
}
