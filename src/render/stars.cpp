/*
 * stars.cpp - Scene package - handles star rendering
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/scene.h"
#include "render/stars.h"

using namespace ofs::renderer;
using namespace ofs::universe;

void Scene::initStarRenderer()
{

	starRenderer = new StarRenderer();

	starRenderer->ctx = &gl;
	starRenderer->pgm = smgr.getShader("star");

	starRenderer->pointStarBuffer = new StarVertex();
	starRenderer->pointStarBuffer->setProgram(starRenderer->pgm);
	starRenderer->pointStarBuffer->setBuffer(starRenderer->vbuf);

	starRenderer->glareStarBuffer = new StarVertex();
	starRenderer->glareStarBuffer->setProgram(starRenderer->pgm);
	starRenderer->glareStarBuffer->setBuffer(starRenderer->vbuf);
}

void StarRenderer::process(const CelestialStar *star, double dist, double appMag) const
{
//	vec3d_t spos, rpos;
//	double  srad;
//	double  rdist;
//	double  objSize;
//	double  discSize;
//	double  discScale;
//	double  alpha, ptSize;
//	Color   color;
//
//	// Calculate relative position between star and camera positions.
//	spos  = star.getPosition(0) * KM_PER_PC;
//	rpos  = spos - cpos;
//	rdist = glm::length(rpos);
//
//	// Calculate apparent size of star in view field
//	srad    = star.getRadius();
//	objSize = ((srad / rdist) * 2.0) / pxSize;
//
////	if (star.getHIPNumber() == 0)
////		cout << "Sun distance: " << rdist << " size: " << glm::degrees(asin(srad/rdist) * 2.0)
////			 << " pixel: " << pxSize  << " -> " << srad / (rdist * pxSize) << endl;
//
//	if (objSize > pxSize) {
//		discSize = objSize;
//		alpha = 1.0;
//	} else {
//		alpha  = faintestMag - appMag;
//		discSize = baseSize;
//		if (alpha > 1.0) {
//			discScale = min(pow(2.0, 0.3 * (saturationMag - appMag)), 100.0);
//			discSize *= discScale;
//			alpha = 1.0;
//		} else if (alpha < 0.0)
//			alpha = 0.0;
//	}
//
//	color  = starColors->lookup(star.getTemperature());
//	color.setAlpha(alpha);
//
////	if (star.getHIPNumber() == 0) {
////		cout << "Star size: " << discSize << " Position: " << rpos.x << "," << rpos.y << "," << rpos.z << endl;
////		cout << "Star color: " << color.getRed() << "," << color.getGreen() << "," << color.getBlue() << "," << color.getAlpha() << endl;
////		discSize = 20.0;
//////		rpos = -rpos;
//////		starBuffer->addStar(rpos, color, discSize);
////	}
//
////	if (spos == vec3d_t(0, 0, 0))
////		cout << "HIP " << star.getHIPNumber() << " at origin" << endl;
//
//	// Finally, now display star
////	cout << "@@@ Adding a star..." << endl;
//	starBuffer->addStar(rpos, color, discSize);
}

//void Scene::buildGaussDiscStar(uint32_t log2Size, double scale, double power)
//{
//	uint32_t size = 1u << log2Size;
//	double sigma = scale / 2.3245;
//	double isig2 = 1.0 / (2.0 * sigma * sigma);
//	double s = 1.0 / (sigma * sqrt(PI * 2.0));
//
//	for (uint32_t yidx = 0; yidx < size; yidx++)
//	{
//		double y = double(yidx) - size / 2.0;
//		for (uint32_t xidx = 0; xidx < size; xidx++)
//		{
//			double x = double(xidx) - size / 2.0;
//			auto r2 = x*x + y*y;
//			auto f = s * exp(-r2 * isig2) * power;
//			auto val = min(f, 1.0);
//			cout << fmt::sprintf(" %.6lf", val);
////			data[(yidx * size) + xidx] = uint8_t(255.99 * min(f, 1.0));
//		}
//		cout << endl;
//	}
//}

uint16_t *Scene::buildGaussGlareStar(uint32_t log2Size, double scale, double base)
{
	uint32_t size = 1u << log2Size;
	uint16_t *data = new uint16_t[size * size];

	for (uint32_t yidx = 0; yidx < size; yidx++)
	{
		float y = float(yidx) - size / 2.0f;
		for (uint32_t xidx = 0; xidx < size; xidx++)
		{
			float x = float(xidx) - size / 2.0f;
			auto r = float(sqrt(x*x + y*y));
			auto f = float(pow(base, r * scale));
			auto val = uint16_t(65535.99f * min(f, 1.0f));
//			cout << fmt::sprintf(" %05d", val);
			data[(yidx * size) + xidx] = val;
		}
//		cout << endl;
	}

	return data;
}
