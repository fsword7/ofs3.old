/*
 * coreapp.cpp - main core application package
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "main/coreapp.h"

using namespace ofs;

void CoreApp::init()
{
}

void CoreApp::initEngine()
{
	engine = new Engine();
	engine->init();
}

void CoreApp::clean()
{
	delete engine;
}

void CoreApp::update()
{
	// Update input controls
}

void CoreApp::render()
{
	engine->render();
}
