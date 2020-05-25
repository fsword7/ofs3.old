/*
 * scene.h - scene renderer package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "engine/player.h"
#include "universe/object.h"
#include "universe/universe.h"

#include "render/gl/context.h"
#include "render/gl/buffer.h"
#include "render/gl/shader.h"
#include "render/olentry.h"
#include "render/camera.h"

namespace ofs::renderer
{
	class StarRenderer;

	struct RenderParameter
	{
		double  now;  // Current julian time

		// player/vessel position/orientation
		vec3d_t ppos; // Current vessel position
		quatd_t prot; // Current vessel orientation

		// First/third person view position/orientation
		vec3d_t cpos; // Current camera position (vessel reference frame)
		quatd_t crot; // Current camera orientation (vessel reference frame)
	};

	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		inline Context &getContext() { return gl; }

		Camera *getCamera(int idx = 0);

		void init();
		void render(ofs::engine::Player *player, ofs::universe::Universe *universe);

	private:
		void initStarRenderer();

//		void buildGaussDiscStar(uint32_t log2Size, double scale, double base);
		uint16_t *buildGaussGlareStar(uint32_t log2Size, double scale, double base);

	private:
		Context gl;

		vector<Camera *> views;

		vector<ObjectListEntry *> objectList;
		vector<const ofs::universe::CelestialStar *> closeStars;

		RenderParameter prm;

		ShaderManager  smgr;
		StarRenderer  *starRenderer = nullptr;

		double faintestMagnitude = 6.0;
		Color ambientColor = { 0.1, 0.1, 0.1 };
		Color skyColor = { 0.0, 0.0, 0.0 };
	};
}
