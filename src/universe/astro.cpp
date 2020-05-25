/*
 * astro.cpp - astronomical math package
 *
 *  Created on: May 25, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "universe/astro.h"

using namespace ofs::astro;

vec3d_t ofs::astro::convertCelestialToEcliptic(double ra, double dec, double dist)
{
	double  theta, phi;
	double  x, y, z;
	vec3d_t rot(J2000Obliquity, 0, 0);

	theta = glm::radians(ra) + PI;
	phi   = glm::radians(dec - 90.0);

	vec3d_t cpos = vec3d_t(sin(phi) * cos(theta),
						   cos(phi),
						   sin(phi) * -sin(theta));

	return (cpos * glm::dquat(rot)) * dist;
}
