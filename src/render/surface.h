/*
 * surface.h - OFS surface/terrain package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "render/gl/mesh.h"
#include "render/renderprm.h"
#include "util/tree.h"
#include "engine/object.h"

namespace ofs::renderer
{
	class Surface;

	class Tile : public Tree<Tile, QTREE_NODES>
	{
	public:
		Tile(Surface &mgr, uint32_t lod, int32_t ilat, uint32_t ilng);
		~Tile() = default;

		void update();
		void render(Context &gl);

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
			appEmissive = 0x00000001,
			appInvalid  = 0x80000000
		};

		inline bool isInvalid() const { return flags & appInvalid; }

		Surface(const Object &obj) : object(obj) {}
		~Surface() = default;

		void init(Context &gl);
		void clear();

		void render(Context &gl, const vec3d_t &opos, double zCenter, const RenderParameter &prm);

	private:
		void createEllipsoid(int level, int ilat, int ilng, int xGrids, int yGrids,
			Mesh &mesh);

	public:
		// Surface information properties
		uint32_t flags = appInvalid;
		Color    color = Color(1, 1, 1);

	private:
		const Object &object;
		Color defaultColor = Color(1, 1, 1);

		ShaderProgram *pgm = nullptr;

		Tile *rootTiles[2] = { nullptr, nullptr };
	};
}
