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

private:
	ObjectType objType;
	vector<string> objNames{1};

protected:
	double geomRadius = 0.0;
};
