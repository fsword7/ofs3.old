/*
 * system.cpp - solar system object rendering package
 *
 *  Created on: Jun 2, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/scene.h"

using namespace ofs::universe;
using namespace ofs::renderer;

void Scene::renderStar(const CelestialStar *star,
	vec3d_t opos, double dist, double zCenter, double appMag, double now)
{
	double radius = star->getGeometryRadius();
	double objSizeInPixels = radius / (dist * prm.pixelSize);
	Color  color = starColors->lookup(star->getTemperature());

//	cout << fmt::sprintf("Object size in pixels: %lf\n", objSizeInPixels) << flush;

	// Render object as surface if object is enough close.
	if (objSizeInPixels > 1)
	{
		Surface &smgr = star->getSurface();

		if (smgr.isInvalid())
			smgr.init(gl);

		smgr.color = color;
		smgr.flags = Surface::appEmissive;


		smgr.render(gl, opos, zCenter, prm);
	}

	// Render object as point.
}

void Scene::renderBody(const CelestialBody *body,
	vec3d_t opos, double dist, double zCenter, double appMag, double now)
{
}

void Scene::renderObjectEntry(const ObjectListEntry &ole)
{
	switch (ole.type)
	{
	case ObjectListEntry::objRenderableStar:
		renderStar(static_cast<const CelestialStar *>(ole.object),
			ole.position, ole.distance, ole.zCenter, ole.appMag, prm.now);
		break;

	case ObjectListEntry::objRenderableBody:
		renderBody(static_cast<const CelestialBody *>(ole.object),
			ole.position, ole.distance, ole.zCenter, ole.appMag, prm.now);
		break;
	}
}

void Scene::renderSolarSystemObjects()
{
	gl.setPolygonMode(Context::modeWireframe);

	for (int idx = 0; idx < objectList.size(); idx++)
	{
		renderObjectEntry(objectList[idx]);
	}

	gl.setPolygonMode(Context::modeFill);
}
