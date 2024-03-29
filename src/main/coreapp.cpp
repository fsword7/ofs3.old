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

void CoreApp::mouseDialWheel(float motion, int state)
{
	Player *player = engine->getPlayer();
//
//	double dzoom = dy / height;
//	player->dolly(dzoom * 5);
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
//	if (stateKey[keyLeft])
//		tv.x += dt * 3000.0;
//	if (stateKey[keyRight])
//		tv.x -= dt * 3000.0;

	// Y-axis move control
//	if (stateKey[keyDown])
//		tv.y += dt * 3000.0;
//	if (stateKey[keyUp])
//		tv.y -= dt * 3000.0;

	// Z-axis move control
	if (stateKey[keyPad3])
		tv.z += dt * 3000.0;
	if (stateKey[keyPad1])
		tv.z -= dt * 3000.0;

	// Keyboard dolly control
	if (stateKey[keyHome])
		player->dolly(-dt * 2.0);
	if (stateKey[keyEnd])
		player->dolly(dt * 2.0);

	// Orbital X/Y-axis control
	if (player->getReferenceObject() != nullptr)
	{
		quatd_t rot = quatd_t(1.0, 0.0, 0.0, 0.0);
		double  coarse = 1;

		if (stateKey[keyLeft])
			rot *= yrot(-dt * keyRotationAccel * coarse);
		if (stateKey[keyRight])
			rot *= yrot(dt * keyRotationAccel * coarse);
		if (stateKey[keyUp])
			rot *= xrot(-dt * keyRotationAccel * coarse);
		if (stateKey[keyDown])
			rot *= xrot(dt * keyRotationAccel * coarse);

		player->orbit(rot);
	}

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
