/*
 * camera.h - camera/view package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#pragma once

namespace ofs::renderer
{
	class Camera
	{
	public:
		enum ViewType {
			viewMainScreen,
			viewMultiFunction1,
			viewMultiFunction2,
		};

		Camera(ViewType view);
		~Camera() = default;

		inline ViewType getViewType() const { return viewType; }
		inline double getFOVY() const { return fovY; }
		inline double getAspect() const { return aspect; }

		inline vec3d_t getOffsetPosition() const { return opos; }
		inline quatd_t getOffsetOrientation() const { return orot; }

		double computePixelSize() const;

	private:
		ViewType viewType = viewMainScreen;

		// Screen dimension parameters
		uint32_t width  = 1;
		uint32_t height = 1;
		double   aspect = width / height;

		// field of view in Y axis [raidians]
		double fovY = glm::radians(OFS_DEFAULT_FOV);

		// offset position in player reference frame
		vec3d_t opos = { 0.0, 0.0, 0.0 };
		quatd_t orot = { 1.0, 0.0, 0.0, 0.0 };
	};
}
