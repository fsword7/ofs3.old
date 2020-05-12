/*
 * scene.cpp - Scene renderer package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/scene.h"

using namespace ofs::renderer;

void Scene::init()
{

//	double fwhm = pow(2.0, 4.0 * 0.3);
//	double power = pow(2.0, 4.0);
//	buildGaussDiscStar(4, fwhm, power);

//	double fwhm = 25.0 / pow(2.0, 4.0);
//	double power = 0.66;
//	buildGaussGlareStar(4, fwhm, power);

}

void Scene::render()
{
	gl.start();

	gl.finish();
}
