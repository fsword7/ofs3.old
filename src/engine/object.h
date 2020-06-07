/*
 * object.h - Object package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#pragma once

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

protected:
	virtual void computeCullingRadius() = 0;

private:
	ObjectType objType;
	vector<string> objNames{1};

protected:
	vec3d_t objPosition    = { 0, 0, 0 };
	quatd_t objOrientation = { 1, 0, 0, 0 };

	double geomRadius  = 0.0;
	double cullRadius  = 0.0;
	double orbitRadius = 0.0;
};
