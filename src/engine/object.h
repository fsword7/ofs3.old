/*
 * object.h - Object package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "engine/frame.h"

namespace ofs::engine
{
	class Object
	{
	public:
		enum ObjectType {
			objUnknown = 0,
			objPlayer,
			objCelestial
		};

		Object(const string &name, ObjectType type) : objType(type)
		{
			objNames[0] = name;
		}
		virtual ~Object() = default;

		inline void setName(const string &name) { objNames[0] = name; }

		inline string getName() const { return objNames[0]; }
		inline string getNames(int idx = 0) const
			{ return idx >= 0 && idx < objNames.size() ? objNames[idx] : ""; }

		inline double getGeometryRadius() const { return geomRadius; }
		inline double getCullingRadius() const { return cullRadius; }
		inline double getOrbitalRadius() const { return orbitRadius; }

		inline vec3d_t getGlobalPosition(double t = 0) const { return objPosition; }
		inline vec3d_t getLocalPosition(double t = 0) const { return objPosition; }
		inline quatd_t getOrientation(double t = 0) const { return objOrientation; }

		inline Frame *getOrbitFrame() const { return orbitFrame; }
		inline Frame *getBodyFrame() const { return bodyFrame; }
		inline void   setOrbitFrame(Frame *frame) { orbitFrame = frame; }
		inline void   setBodyFrame(Frame *frame) { bodyFrame = frame; }

	protected:
		virtual void computeCullingRadius() = 0;

	private:
		ObjectType objType = objUnknown;
		vector<string> objNames{1};

	protected:
		// Reference frame for orbit plane and body
		Frame  *orbitFrame = nullptr;
		Frame  *bodyFrame  = nullptr;

		vec3d_t objPosition    = { 0, 0, 0 };
		quatd_t objOrientation = { 1, 0, 0, 0 };

		double geomRadius  = 0.0;
		double cullRadius  = 0.0;
		double orbitRadius = 0.0;
	};
}
