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
	width  = OFS_DEFAULT_WIDTH;
	height = OFS_DEFAULT_HEIGHT;

	engine = new Engine();
	engine->init(width, height);
}

void CoreApp::clean()
{
	delete engine;
}

void CoreApp::resize(uint32_t w, uint32_t h)
{
	width  = w;
	height = h;
	engine->resize(w, h);
}

// ******** Mouse Control Routines ********

void CoreApp::mouseMove(float x, float y, int state)
{
	using Camera = ofs::renderer::Camera;
	using Scene = ofs::renderer::Scene;

	float dx = x - lastX;
	float dy = y - lastY;

	Player *player = engine->getPlayer();
	Scene *scene = engine->getScene();

	// Rotate camera around
	if (state & mouseRightButton) {
//		if (checkAnyFlags(state, keyControl)) {
//			double dzoom = dy / height;
//			player->dolly(dzoom * 5);
//		} else {
			Camera *cam = scene->getCamera();
			double fov  = cam->getFOVY();

//			double coarseness = player->computeCoarseness(1.5);
			double coarseness = glm::degrees(fov) / 30.0;

			quatd_t rot = xrot(dy / height * coarseness) * yrot(dx / width * coarseness);
			player->orbit(rot);
//		}
	} else if (state & mouseLeftButton) {
		Camera *cam = scene->getCamera();
		double fov  = cam->getFOVY();

		double coarseness = glm::degrees(fov) / 30.0;

		quatd_t rot = xrot(dy / height * coarseness) * yrot(dx / width * coarseness);
		player->rotate(rot);
	}

	// Save current mouse motion for next event.
	lastX = x;
	lastY = y;
}

void CoreApp::mousePressButtonDown(float x, float y, int state)
{
}

void CoreApp::mousePressButtonUp(float x, float y, int state)
{
//	View *view = nullptr;
//	float vx = 0.0f, vy = 0.0f;
//
//	if (state & mouseLeftButton) {
//		view = pickView(x, y);
//		if (view != nullptr)
//			view->map(x/float(width), y/float(height), vx, vy);
//
//		vec3d_t ray = player->getRay(vx, vy);
//
//	}
}

void CoreApp::mouseDialWheel(float motion)
{
}

// ******** Keyboard Control Routines ********

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
	vec3d_t pav, oav, tv;

//	dt  = jdate->update();
	pav = player->getPlayerAngularVelocity();
	oav = player->getOrbitalAngularVelocity();
	tv  = player->getTravelVelocity();

	// Keyboard rotation and travel control
	// X-axis rotation control
	if (stateKey[keyPad8])
		pav += vec3d_t(dt * keyRotationAccel, 0, 0);
	if (stateKey[keyPad2])
		pav += vec3d_t(dt * -keyRotationAccel, 0, 0);
//	if (stateKey[keyPad8])
//		oav += vec3d_t(dt * keyRotationAccel, 0, 0);
//	if (stateKey[keyPad2])
//		oav += vec3d_t(dt * -keyRotationAccel, 0, 0);

	// Y-axis rotation control
	if (stateKey[keyPad4])
		pav += vec3d_t(0, dt * keyRotationAccel, 0);
	if (stateKey[keyPad6])
		pav += vec3d_t(0, dt * -keyRotationAccel, 0);
//	if (stateKey[keyPad4])
//		oav += vec3d_t(0, dt * keyRotationAccel, 0);
//	if (stateKey[keyPad6])
//		oav += vec3d_t(0, dt * -keyRotationAccel, 0);

	// Z-axis rotation control
	if (stateKey[keyPad7])
		pav += vec3d_t(0, 0, dt * -keyRotationAccel);
	if (stateKey[keyPad9])
		pav += vec3d_t(0, 0, dt * keyRotationAccel);
//	if (stateKey[keyPad7])
//		oav += vec3d_t(0, 0, dt * -keyRotationAccel);
//	if (stateKey[keyPad9])
//		oav += vec3d_t(0, 0, dt * keyRotationAccel);


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
		pav *= exp(-dt * keyRotationBrake);
//		oav *= exp(-dt * keyRotationBrake);
		tv  *= exp(-dt * keyTravelBrake);
	}

	player->setPlayerAngularVelocity(pav);
	player->setOrbitalAngularVelocity(oav);
	player->setTravelVelocity(tv);
	engine->update(dt);
}

void CoreApp::render()
{
	engine->render();
}
