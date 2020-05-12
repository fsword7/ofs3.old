/*
 * stars.cpp - Scene package - handles star rendering
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/scene.h"

using namespace ofs::renderer;

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

void Scene::buildGaussGlareStar(uint32_t log2Size, double scale, double base)
{
	uint32_t size = 1u << log2Size;

	for (uint32_t yidx = 0; yidx < size; yidx++)
	{
		double y = double(yidx) - size / 2.0;
		for (uint32_t xidx = 0; xidx < size; xidx++)
		{
			double x = double(xidx) - size / 2.0;
			auto r = sqrt(x*x + y*y);
			auto f = pow(base, r * scale);
			auto val = min(f, 1.0);
			cout << fmt::sprintf(" %.6lf", val);
//			data[(yidx * size) + xidx] = uint8_t(255.99 * min(f, 1.0));
		}
		cout << endl;
	}
}



