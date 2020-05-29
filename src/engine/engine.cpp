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
	Object *obj = universe->find("Sol");
	if (obj != nullptr) {
//		cout << "Star name: " << sun->getName() << endl << flush;
		player->move(*obj);
		player->look(*obj);
		player->setSelectedObject(obj);
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
