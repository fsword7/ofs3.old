/*
 * star.cpp - Celestial star package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "universe/astro.h"
#include "universe/object.h"

using namespace ofs::astro;
using namespace ofs::universe;

CelestialStar *CelestialStar::createSun()
{
 	CelestialStar *star = new CelestialStar("Sol");

	star->ra			= 0.0;
	star->dec			= 0.0;
	star->plx			= 0.0;
	star->absMag		= SOLAR_ABSMAG;
	star->bMag			= 0.0;
	star->vMag			= 0.0;
	star->ci			= SOLAR_CI;
	star->lum			= SOLAR_LUMINOSITY;
	star->temp			= SOLAR_TEMPERATURE;

	star->knownFlags	= csKnownRadius;
	star->geomRadius	= SOLAR_RADIUS;

	star->hipNumber		= 0;

	return star;
}

CelestialStar *CelestialStar::create(double ra, double dec, double plx, double pc,
		const char *spType, double appMag, double ci, double lum)
{

	CelestialStar *star = new CelestialStar();

	star->objPosition = convertCelestialToEcliptic(ra, dec, pc);

	int temp = (int)(4600 * (1/((ci*0.92)+1.7) + 1/((ci*0.92)+0.62)));

	star->ra  = ra;
	star->dec = dec;
	star->plx = plx;
	star->absMag = convertAppToAbsMag(appMag, pc);
	star->bMag = appMag + ci;
	star->vMag = appMag;
	star->ci  = ci;
	star->lum = lum;
	star->temp = temp;

	return star;
}
