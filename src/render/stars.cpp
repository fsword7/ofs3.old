/*
 * stars.cpp - Scene package - handles star rendering
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/scene.h"

using namespace ofs::renderer;

void Scene::initStarRenderer()
{

	starRenderer.ctx = &gl;
	starRenderer.pgm = smgr.getShader("star");

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
