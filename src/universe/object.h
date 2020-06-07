/*
 * body.h - Celestial body package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "engine/object.h"
#include "render/surface.h"

namespace ofs::universe
{
	enum SpectralClass
	{
		starSpectral_Unknown = 0,
		starSpectral_O,
		starSpectral_B,
		starSpectral_A,
		starSpectral_F,
		starSpectral_G,
		starSpectral_K,
		starSpectral_M,
		starSpectral_R,
		starSpectral_S,
		starSpectral_N,
		starSpectral_WC,
		starSpectral_WN,
		starSpectral_L,
		starSpectral_T,
		starSpectral_C,
		starSpectral_DA,
		starSpectral_DB,
		starSpectral_DC,
		starSpectral_DO,
		starSpectral_DQ,
		starSpectral_DZ,
		starSpectral_D,
		starSpectral_DX
	};

	// Hierarchical planetary system
	class PlanetarySystem
	{
	public:

		inline int getSystemSize() const { return satellites.size(); }

	private:
		vector<PlanetarySystem *> satellites;

	};

	class CelestialBody : public Object
	{
	public:
		enum CelestialType {
			cbUnknown = 0,
			cbStar,
			cbPlanet,
			cbDwarfPlanet,
			cbMoon,
			cbComet
		};

		CelestialBody(const string &name, CelestialType type)
		: Object(name, objCelestial), cbType(type), surface(*this)
		{
		}

		ofs::renderer::Surface &getSurface() const { return surface; }

//		void initSurface(Context &gl) const;

	private:
		CelestialType cbType = cbUnknown;

	protected:
		mutable ofs::renderer::Surface surface;

	};

	class CelestialStar : public CelestialBody
	{
	public:
		enum {
			csKnownRadius   = 1,
			csKnownRotation = 2,
			csKnownSurface  = 4
		};

		CelestialStar() : CelestialBody("(noname)", cbStar) {}
		CelestialStar(const string &name) : CelestialBody(name, cbStar) {}

		static CelestialStar *createSun();
		static CelestialStar *create(double ra, double dec, double plx, double pc,
			const char *spType, double appMag, double ci, double lum);

		inline void setIndex(int idx) { hipNumber = idx; }

		inline int getIndex() const { return hipNumber; }
		inline int getTemperature() const { return temp; }
		inline double getAbsMag() const { return absMag; }

	private:
		uint32_t knownFlags = 0;

		int hipNumber;

		// J2000 Equator coordinates
		double ra, dec, plx;

		// Star atmosphere parameters
		double absMag;
		double bMag, vMag;
		double ci, lum;
		int    temp;
	};
}
