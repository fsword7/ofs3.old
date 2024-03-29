/*
 * body.cpp - Celestial body package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "universe/object.h"

using namespace ofs::universe;
using namespace ofs::renderer;

//void CelestialBody::initSurface(Context &gl)
//{
//	surface.init(gl);
//}

void CelestialBody::computeCullingRadius()
{
	cullRadius = geomRadius;
}
