/*
 * scene.h - scene renderer package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "engine/player.h"
#include "universe/object.h"
#include "universe/stardb.h"
#include "universe/universe.h"

#include "render/gl/context.h"
#include "render/gl/buffer.h"
#include "render/gl/shader.h"
#include "render/olentry.h"
#include "render/renderprm.h"
#include "render/camera.h"
#include "render/starcolors.h"

#define DIST_NEAR	0.0001
//#define DIST_FAR	1.0e15
#define DIST_FAR 1.0e10

namespace ofs::renderer
{
	using Player = ofs::engine::Player;
	using CelestialStar = ofs::universe::CelestialStar;
	using CelestialBody = ofs::universe::CelestialBody;
	using StarCatalog = ofs::universe::StarCatalog;
	using Universe = ofs::universe::Universe;

	class StarRenderer;
	class Camera;

//	struct RenderParameter
//	{
//		double  now;  // Current julian time
//
//		Camera *cam;  // Current view
//		double  pixelSize; // pixel size in current view
//
//		// player/vessel position/orientation
//		vec3d_t ppos; // Current vessel position
//		quatd_t prot; // Current vessel orientation
//
//		// First/third person view position/orientation
//		vec3d_t cpos; // Current camera position (vessel reference frame)
//		quatd_t crot; // Current camera orientation (vessel reference frame)
//	};

	struct VertexLine
	{
		vec3f_t lpos;
		Color   color;
	};

	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		inline Context &getContext() { return gl; }

		Camera *getCamera(int idx = 0);

		void init(const Universe &universe, int width, int height);
		void resize(int width, int height);
		void render(Player *player, Universe *universe);

	private:
		void initStarRenderer();
		void initConstellations(const Universe &universe);
		void initLightSources();

//		void buildGaussDiscStar(uint32_t log2Size, double scale, double base);
		uint16_t *buildGaussGlareStar(uint32_t log2Size, double scale, double base);

		void renderStars(const StarCatalog &stardb, double faintest);
		void renderConstellations(const Universe &universe, const Player &player);

		// Rendering solar system function calls
		void renderStar(const CelestialStar *star,
			vec3d_t opos, double dist, double zCenter, double appMag, double now);
		void renderBody(const CelestialBody *body,
			vec3d_t opos, double dist, double zCenter, double appMag, double now);
		void renderObjectEntry(const ObjectListEntry &ole);
		void renderSolarSystemObjects();

	private:
		Context gl;

		vector<Camera *> views;

		vector<ObjectListEntry> objectList;
		vector<const CelestialStar *> closeStars;

		Camera *cam = nullptr;
		RenderParameter prm;

		StarColors    *starColors = nullptr;
		StarRenderer  *starRenderer = nullptr;

		ShaderProgram *pgmStar = nullptr;
		VertexBuffer  *vbufStar = nullptr;

		ShaderProgram *pgmAsterism = nullptr;
		VertexBuffer  *vbufAsterism = nullptr;
		uint32_t asterismLines = 0;

		double faintestMagnitude = 6.0;
		double saturationMagnitude = 0.0;
		Color ambientColor = { 0.1, 0.1, 0.1 };
		Color skyColor = { 0.0, 0.0, 0.0 };
	};
}
