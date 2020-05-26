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
	// Initialize state keys
	for (int key = 0; key < 512; key++)
		stateKey[key] = false;

	// Initialize velocity control
	keyRotationAccel = glm::radians(OFS_DEFAULT_FOV);
	keyRotationBrake = glm::radians(OFS_DEFAULT_FOV) * 3.0;
	keyTravelAccel   = 2.0;
	keyTravelBrake   = 5.0;

	lastX = -1;
	lastY = -1;
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

void CoreApp::resize(int width, int height)
{
	engine->resize(width, height);
}

void CoreApp::keyPress(keyCode code, int modifiers, bool down)
{
	stateKey[code] = down;
}

void CoreApp::keyEntered(char32_t ch, int modifiers)
{
//	cout << fmt::sprintf("Key pressed: %c\n", (char)ch) << flush;
//	switch (ch) {
//	case L'k':
//		engine->setTimeWarp(engine->getTimeWarp() * 2.0);
//		break;
//	case L'l':
//		engine->setTimeWarp(engine->getTimeWarp() / 2.0);
//		break;
//	}
}

void CoreApp::update()
{
	// Update input controls
//	Date *jdate = engine->getRealTime();

	Player *player = engine->getPlayer();

	double  dt = 0.01;
	vec3d_t av, tv;

//	dt = jdate->update();
	av = player->getAngularVelocity();
	tv = player->getTravelVelocity();

	// Keyboard rotation and travel control
	// X-axis rotation control
	if (stateKey[keyPad8])
		av += vec3d_t(dt * keyRotationAccel, 0, 0);
	if (stateKey[keyPad2])
		av += vec3d_t(dt * -keyRotationAccel, 0, 0);

	// Y-axis rotation control
	if (stateKey[keyPad4])
		av += vec3d_t(0, dt * keyRotationAccel, 0);
	if (stateKey[keyPad6])
		av += vec3d_t(0, dt * -keyRotationAccel, 0);

	// Z-axis rotation control
	if (stateKey[keyPad7])
		av += vec3d_t(0, 0, dt * -keyRotationAccel);
	if (stateKey[keyPad9])
		av += vec3d_t(0, 0, dt * keyRotationAccel);

	// Travel velocity control
	// X-axis move control
	if (stateKey[keyLeft])
		tv.x += dt * 3000.0;
	if (stateKey[keyRight])
		tv.x -= dt * 3000.0;

	// Y-axis move control
	if (stateKey[keyDown])
		tv.y += dt * 3000.0;
	if (stateKey[keyUp])
		tv.y -= dt * 3000.0;

	// Z-axis move control
	if (stateKey[keyPad3])
		tv.z += dt * 3000.0;
	if (stateKey[keyPad1])
		tv.z -= dt * 3000.0;

	// Braking velocity control
	if (stateKey[keyPad5])
	{
		av *= exp(-dt * keyRotationBrake);
		tv *= exp(-dt * keyTravelBrake);
	}

	player->setAngularVelocity(av);
	player->setTravelVelocity(tv);
	engine->update(dt);
}

void CoreApp::render()
{
	engine->render();
}
