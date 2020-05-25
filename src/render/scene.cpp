/*
 * scene.cpp - Scene renderer package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/player.h"
#include "universe/universe.h"
#include "render/gl/context.h"
#include "render/gl/shader.h"
#include "render/scene.h"

using namespace ofs::engine;
using namespace ofs::universe;
using namespace ofs::renderer;

Scene::Scene()
: smgr(&gl)
{
}

void Scene::init()
{

//	double fwhm = pow(2.0, 4.0 * 0.3);
//	double power = pow(2.0, 4.0);
//	buildGaussDiscStar(4, fwhm, power);

//	double fwhm = 25.0 / pow(2.0, 3.0);
//	double power = 0.66;
//	uint16_t *data = buildGaussGlareStar(4, fwhm, power);
//
//	delete data;

	initStarRenderer();

	// Initialize main view screen
	Camera *cam = new Camera(Camera::viewMainScreen);
	views.push_back(cam);
}

Camera *Scene::getCamera(int idx)
{
	if (idx >= 0 && idx < views.size())
		return views[idx];
	return nullptr;
}

void Scene::render(Player *player, Universe *universe)
{
	Camera *cam = views[0];

	// Initial rendering parameter for vessel and camera
	prm.now  = player->getCurrentTime();
	prm.ppos = player->getGlobalPosition();
	prm.prot = player->getGlobalOrientation();
	prm.cpos = prm.ppos + cam->getOffsetPosition();
	prm.crot = prm.prot * cam->getOffsetOrientation();

	// Clear all current lists each frame
	objectList.clear();
	closeStars.clear();

//	universe->findCloseStars(prm.cpos, 1.0, closeStars);

	gl.start();

	gl.finish();
}
