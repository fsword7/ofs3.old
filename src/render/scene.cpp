/*
 * scene.cpp - Scene renderer package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/context.h"
#include "render/gl/shader.h"
#include "render/scene.h"

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
}

void Scene::render()
{
	gl.start();

	gl.finish();
}
