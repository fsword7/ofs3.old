/*
 * renderprm.h - render parameter package
 *
 *  Created on: May 25, 2020
 *      Author: Tim Stark
 */

#pragma once

struct RenderParameter
{
	double  now;  // Current julian time

//	Camera *cam;  // Current view
	double  pixelSize; // pixel size in current view

	// player/vessel position/orientation
	vec3d_t ppos; // Current vessel position
	quatd_t prot; // Current vessel orientation

	// First/third person view position/orientation
	vec3d_t cpos;   // Current camera position (vessel reference frame)
	quatd_t crot;   // Current camera orientation (vessel reference frame)
	vec3d_t vpnorm; // view normal (clipping)

	double  fov;
	double  aspect;

	mat4d_t dmProj;
	mat4d_t dmView;
};
