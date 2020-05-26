/*
 * stars.h - star renderer package
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/gl/context.h"
#include "render/gl/buffer.h"
#include "render/gl/shader.h"
#include "render/gl/stars.h"
#include "universe/object.h"
#include "universe/handler.h"

using namespace ofs::universe;

namespace ofs::renderer
{
	class StarRenderer : public ofsHandler
	{
	public:
		StarRenderer() = default;
		~StarRenderer() = default;

		void process(const CelestialStar *star, double dist, double appMag) const;

	public:
		Context *ctx = nullptr;
		ShaderProgram *pgm = nullptr;
		VertexBuffer *vbuf = nullptr;

		StarColors *starColors = nullptr;
		StarVertex *pointStarBuffer = nullptr;
		StarVertex *glareStarBuffer = nullptr;

		vec3d_t viewPosition = { 0.0, 0.0, 0.0}; // view position
		double  pixelSize = 0.0;
		double  faintestMagnitude = 0.0;
		double  faintestMagnitudeNight = 0.0;
		double  saturationMagnitude = 0.0;
	};
}
