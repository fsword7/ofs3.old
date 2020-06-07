/*
 * frame.cpp - reference frame package
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/frame.h"
#include "engine/object.h"

using namespace ofs::engine;

// ******** ReferenceFrame (Frame) ********

Frame::Frame(const Object *object, const Frame *parent)
: center(object), parent(parent)
{
	lock();
}

int Frame::lock() const
{
	return ++refCount;
}

int Frame::release() const
{
	int count = --refCount;
	if (refCount <= 0)
		delete this;
	return count;
}

vec3d_t Frame::fromAstrocentric(const vec3d_t &upos, double tjd)
{
	if (center == nullptr)
		return upos;

	vec3d_t opos = center->getGlobalPosition(tjd);
	quatd_t orot = glm::conjugate(getOrientation(tjd));
	vec3d_t rpos = (opos - upos) * orot;

//	cout << fmt::sprintf("Center: P(%lf,%lf,%lf) Q(%lf,%lf,%lf,%lf)\n",
//		opos.x, opos.y, opos.z, orot.w, orot.x, orot.y, orot.z);
//	cout << fmt::sprintf(" Frame: U(%lf,%lf,%lf) => L(%lf,%lf,%lf)\n",
//		upos.x, upos.y, upos.z, rpos.x, rpos.y, rpos.z);

	return rpos;
}

vec3d_t Frame::toAstrocentric(const vec3d_t &lpos, double tjd)
{
	if (center == nullptr)
		return lpos;

	vec3d_t opos = center->getGlobalPosition(tjd);
	quatd_t orot = getOrientation(tjd);
	vec3d_t rpos = opos + (lpos * orot);

//	cout << fmt::sprintf("Center: P(%lf,%lf,%lf) Q(%lf,%lf,%lf,%lf)\n",
//		opos.x, opos.y, opos.z, orot.w, orot.x, orot.y, orot.z);
//	cout << fmt::sprintf(" Frame: L(%lf,%lf,%lf) => U(%lf,%lf,%lf)\n",
//		lpos.x, lpos.y, lpos.z, rpos.x, rpos.y, rpos.z);

	return rpos;
}


vec3d_t Frame::fromUniversal(const vec3d_t &upos, double tjd)
{
	if (center == nullptr)
		return upos;

	vec3d_t opos = center->getGlobalPosition(tjd);
	quatd_t orot = glm::conjugate(getOrientation(tjd));
	vec3d_t rpos = (opos - upos) * orot;

//	cout << fmt::sprintf("Center: P(%lf,%lf,%lf) Q(%lf,%lf,%lf,%lf)\n",
//		opos.x, opos.y, opos.z, orot.w, orot.x, orot.y, orot.z);
//	cout << fmt::sprintf(" Frame: U(%lf,%lf,%lf) => L(%lf,%lf,%lf)\n",
//		upos.x, upos.y, upos.z, rpos.x, rpos.y, rpos.z);

	return rpos;
}

vec3d_t Frame::toUniversal(const vec3d_t &lpos, double tjd)
{
	if (center == nullptr)
		return lpos;

	vec3d_t opos = center->getGlobalPosition(tjd);
	quatd_t orot = getOrientation(tjd);
	vec3d_t rpos = opos + (lpos * orot);

//	cout << fmt::sprintf("Center: P(%lf,%lf,%lf) Q(%lf,%lf,%lf,%lf)\n",
//		opos.x, opos.y, opos.z, orot.w, orot.x, orot.y, orot.z);
//	cout << fmt::sprintf(" Frame: L(%lf,%lf,%lf) => U(%lf,%lf,%lf)\n",
//		lpos.x, lpos.y, lpos.z, rpos.x, rpos.y, rpos.z);

	return rpos;
}


quatd_t Frame::fromUniversal(const quatd_t &urot, double tjd)
{
	if (center == nullptr)
		return urot;
	return urot * getOrientation(tjd);
}

quatd_t Frame::toUniversal(const quatd_t &lrot, double tjd)
{
	if (center == nullptr)
		return lrot;
	return glm::conjugate(getOrientation(tjd)) * lrot;
}


// ******** J2000 Earth Ecliptic Reference Frame ********

J2000EclipticFrame::J2000EclipticFrame(const Object *obj, const Frame *parent)
: Frame(obj, parent)
{
	frameName = "J2000 Ecliptic Reference Frame";
}
