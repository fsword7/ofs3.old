/*
 * surface.cpp - OFS terrain surface package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/mesh.h"
#include "render/surface.h"

using namespace ofs::renderer;

void Surface::createSphere(int level, int ilat, int ilng, int xGrids, int yGrids)
{
	int nlat = 1 << level;
	int nlng = 2 << level;

	double mlat0 = PI * double(ilat) / double (nlat);
	double mlat1 = PI * double(ilat+1) / double (nlat);
	double mlng0 = PI2 * double(ilng) / double (nlng);
	double mlng1 = PI2 * double(ilng+1) / double(nlng);

	double slat, clat;
	double slng, clng;
	double lat, lng;

	int nVertices = (xGrids+1) * (yGrids+1);
	int nIndices  = 6 * (xGrids * yGrids);

	vec3d_t pos;

	vec3d_t  *vertices = new vec3d_t[nVertices];
	uint16_t *indices = new uint16_t[nIndices];

	vec3d_t *pvtx = vertices;
	for (int y = 0; y <= yGrids; y++)
	{
		lat  = mlat0 + (mlat1-mlat0) * double(y)/double(yGrids);
		slat = sin(lat); clat = cos(lat);

		for (int x = 0; x <= xGrids; x++)
		{
			lng  = mlng0 + (mlng1-mlng0) * double(x)/double(xGrids);
			slng = sin(lng); clng = cos(lng);

			// normalized sphere coordinates
			pos = vec3d_t(slat*clng, clat, slat*-slng);

			*pvtx++ = pos;
		}
	}

	uint16_t *pidx = indices;
	for (int y = 0; y < yGrids; y++)
	{
		for (int x = 0; x < xGrids; x++)
		{
			*pidx++ = (y+0)*(yGrids+1) + (x+0);
			*pidx++ = (y+1)*(yGrids+1) + (x+0);
			*pidx++ = (y+0)*(yGrids+1) + (x+1);

			*pidx++ = (y+1)*(yGrids+1) + (x+0);
			*pidx++ = (y+1)*(yGrids+1) + (x+1);
			*pidx++ = (y+0)*(yGrids+1) + (x+1);
		}
	}

	Mesh *mesh = new Mesh();

	delete [] vertices;
	delete [] indices;
	delete mesh;

//	return mesh;
}
