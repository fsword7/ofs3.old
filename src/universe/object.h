/*
 * body.h - Celestial body package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "engine/object.h"

namespace ofs::universe
{
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

		CelestialBody(string &name, CelestialType type)
		: Object(name, objCelestial), cbType(type)
		{
		}

	private:
		CelestialType cbType = cbUnknown;

	protected:
	};

	class CelestialStar : public CelestialBody
	{
	public:
		CelestialStar(string &name, CelestialType type)
		: CelestialBody(name, type)
		{
		}

	private:
	};
}
