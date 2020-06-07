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

// ******* Surface/terrain tile ********

Tile::Tile(Surface &mgr, uint32_t lod, int32_t ilat, uint32_t ilng)
: tmgr(mgr), lod(lod), ilat(ilat), ilng(ilng)
{

	tmgr.createEllipsoid(lod, ilat, ilng, 32, 32, mesh);
}

void Tile::update()
{
}

void Tile::render(Context &gl)
{
	mesh.render(gl);
}

// ******** Surface/terrain manager ********

void Surface::init(Context &gl)
{
	pgm = gl.getShader("body");

	// Initialize initial tiles at top LOD level
	rootTiles[0] = new Tile(*this, 0, 0, 0);
	rootTiles[1] = new Tile(*this, 0, 0, 1);

	// Clear invalid flag
	flags &= ~appInvalid;
}

void Surface::clear()
{
	// Mark this as invalid
	flags |= appInvalid;

	// Delete all tiles
	for (int idx = 0; idx < 2; idx++) {
		rootTiles[idx]->delChildren();
		delete rootTiles[idx];
		rootTiles[idx] = nullptr;
	}

	pgm = nullptr;
}

void Surface::render(Context &gl, const vec3d_t &opos, double zCenter, const RenderParameter &prm)
{
	pgm->use();

	pgm->setColor("dColor", color);

	mat4d_t dmProj = glm::perspective(prm.fov, prm.aspect,
		zCenter - (object.getGeometryRadius() + 1.0),
		zCenter + (object.getGeometryRadius() + 1.0));
	mat4d_t dmView = glm::transpose(glm::toMat4(prm.crot));

	dmView = glm::translate(dmView, opos);
	mat4f_t mvp = mat4f_t(dmProj * dmView);
	pgm->setMatrix4fv("mvp", mvp);

	// Processing individual tiles on surface
	for (int idx = 0; idx < 2; idx++)
		rootTiles[idx]->update();
	for (int idx = 0; idx < 2; idx++)
		rootTiles[idx]->render(gl);

	pgm->release();
}

void Surface::createEllipsoid(int lod, int ilat, int ilng, int xGrids, int yGrids,
	Mesh &mesh)
{
	int nlat = 1 << lod;
	int nlng = 2 << lod;

	double mlat0 = PI * double(ilat) / double (nlat);
	double mlat1 = PI * double(ilat+1) / double (nlat);
	double mlng0 = PI2 * double(ilng) / double (nlng);
	double mlng1 = PI2 * double(ilng+1) / double(nlng);

	double slat, clat;
	double slng, clng;
	double lat, lng;

	int nVertices = (xGrids+1) * (yGrids+1);
	int nIndices  = 6 * (xGrids * yGrids);

	vec3d_t pos, nml;
	double tu = 0.0;
	double tv = 0.0;

	vtxf_t  *vertices = new vtxf_t[nVertices];
	uint16_t *indices = new uint16_t[nIndices];

	vtxf_t *pvtx = vertices;
	for (int y = 0; y <= yGrids; y++)
	{
		lat  = mlat0 + (mlat1-mlat0) * double(y)/double(yGrids);
		slat = sin(lat); clat = cos(lat);

		for (int x = 0; x <= xGrids; x++, pvtx++)
		{
			lng  = mlng0 + (mlng1-mlng0) * double(x)/double(xGrids);
			slng = sin(lng); clng = cos(lng);

			// normalized sphere coordinates
			nml = vec3d_t(slat*clng, clat, slat*-slng);
			pos = nml * object.getGeometryRadius(); //radius;

			pvtx->vx = float(pos.x);
			pvtx->vy = float(pos.y);
			pvtx->vz = float(pos.z);

//			pvtx->ex = float(pos.x - vtx[vidx].vx);
//			pvtx->ey = float(pos.y - vtx[vidx].vy);
//			pvtx->ez = float(pos.z - vtx[vidx].vz);

			pvtx->nx = float(nml.x);
			pvtx->ny = float(nml.y);
			pvtx->nz = float(nml.z);

			pvtx->tu = float(tu);
			pvtx->tv = float(tv);
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

	mesh.setVertices(nVertices, vertices);
	mesh.setIndices(nIndices, indices);
}
