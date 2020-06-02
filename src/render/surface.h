/*
 * surface.h - OFS surface/terrain package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/gl/mesh.h"
#include "util/tree.h"

namespace ofs::renderer
{
	class Surface;

	class Tile : public Tree<Tile, QTREE_NODES>
	{
	public:
		Tile(Surface &mgr, uint32_t lod, int32_t ilat, uint32_t ilng);
		~Tile() = default;

	private:
		Surface &tmgr;

		uint32_t lod, ilat, ilng;

		Mesh mesh;
	};

	// Surface/terrain manager
	class Surface {
		friend class Tile;

	public:
		enum AppearanceFlags {
			afEmissive = 0x0001
		};

		Surface() = default;
		~Surface() = default;

		void createEllipsoid(int level, int ilat, int ilng, int xGrids, int yGrids,
			Mesh &mesh);

	public:
		uint32_t flags = 0;
		Color    color = Color(1, 1, 1);

	private:
		Color defaultColor = Color(1, 1, 1);

		Tile *rootTiles[2] = { nullptr, nullptr };
	};
}
