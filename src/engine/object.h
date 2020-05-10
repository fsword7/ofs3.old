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

	Object(string &name, ObjectType type) : objType(type) {}

	string getName() const { return objNames[0]; }
	string getNames(int idx = 0) const
		{ return idx >= 0 && idx < objNames.size() ? objNames[idx] : ""; }

private:
	ObjectType objType;
	vector<string> objNames{1};
};
