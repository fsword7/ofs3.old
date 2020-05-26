/*
 * scene.cpp - Scene renderer package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/player.h"
#include "universe/astro.h"
#include "universe/universe.h"
#include "render/gl/context.h"
#include "render/gl/shader.h"
#include "render/scene.h"

using namespace ofs::astro;
using namespace ofs::engine;
using namespace ofs::universe;
using namespace ofs::renderer;

Scene::Scene()
: smgr(&gl)
{
}

void Scene::init(int width, int height)
{

//	double fwhm = pow(2.0, 4.0 * 0.3);
//	double power = pow(2.0, 4.0);
//	buildGaussDiscStar(4, fwhm, power);

//	double fwhm = 25.0 / pow(2.0, 3.0);
//	double power = 0.66;
//	uint16_t *data = buildGaussGlareStar(4, fwhm, power);
//
//	delete data;

	gl.setViewport(width, height);

	initStarRenderer();

	// Initialize main view screen
	Camera *cam = new Camera(Camera::viewMainScreen);
	cam->resize(width, height);
	views.push_back(cam);
}

void Scene::resize(int width, int height)
{
	views[0]->resize(width, height);
	gl.setViewport(width, height);
}

Camera *Scene::getCamera(int idx)
{
	if (idx >= 0 && idx < views.size())
		return views[idx];
	return nullptr;
}

void Scene::render(Player *player, Universe *universe)
{
	// Initial rendering parameter for vessel each frame
	prm.now  = player->getCurrentTime();
	prm.ppos = player->getGlobalPosition();
	prm.prot = player->getGlobalOrientation();

	// Initialize camera parameters each frame
	cam = views[0];
//	prm.cam  = views[0];
	prm.pixelSize = cam->computePixelSize();
	prm.cpos = prm.ppos + cam->getOffsetPosition();
	prm.crot = prm.prot * cam->getOffsetOrientation();

	// Clear all current lists each frame
	objectList.clear();
	closeStars.clear();

	// Find closest stars within one yearlight range
	universe->findCloseStars(prm.cpos, 1.0, closeStars);

	gl.start();

	renderStars(universe->getStarCatalog(), faintestMagnitude);

	gl.finish();
}
