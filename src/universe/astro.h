/*
 * astro.h - Astronomy math package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#pragma once

#define J2000Obliquity glm::radians(23.4392911)

// default solar parameters (our sun)
#define SOLAR_ABSMAG		4.83
#define SOLAR_IRRADIANCE	1367.6
#define SOLAR_POWER			3.8462e26
#define SOLAR_LUMINOSITY	1.0
#define SOLAR_TEMPERATURE	5777.0
#define SOLAR_CI			0.656
#define SOLAR_RADIUS		696000.0
#define SOLAR_MASS			1.9885e30

#define LY_PER_PARSEC		3.26167
#define KM_PER_LY			9460730472580.8
#define AU_PER_PC			206264.81
#define KM_PER_AU			149597870.7
#define AU_PER_LY			(KM_PER_LY / KM_PER_AU)
#define KM_PER_PC			(KM_PER_AU * AU_PER_PC)

namespace ofs::astro
{
	constexpr double G = 6.673889e-11;  // Official gravitational constant [N m/kg^2]
	constexpr double J2000 = 2451545.0; // Epoch 2000 [Jan 1, 2000 at 12:00 UTC]
}
