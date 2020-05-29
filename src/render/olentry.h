/*
 * olentry.h - object list entry package
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#pragma once

namespace ofs::renderer
{
	struct ObjectListEntry
	{
		enum ObjectType {
			objRenderableStar,
			objRenderableBody
		};

		ObjectType	  type;
		const Object *object;
		vec3d_t		  position;
		double		  distance;
		double		  radius;
		double		  appMag;
		double		  pixelSize;
		double		  zCenter;
		bool		  isOpague;
	};
}
