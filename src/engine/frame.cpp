/*
 * frame.cpp - reference frame package
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/frame.h"

using namespace ofs::engine;

vec3d_t ReferenceFrame::fromAstrocentric(const vec3d_t &upos, double tjd)
{
//	if (center == nullptr)
//		return upos;
//
//	vec3d_t opos = center->getGlobalPosition(tjd);
//	quatd_t orot = glm::conjugate(getOrientation(tjd));
//	vec3d_t rpos = (opos - upos) * orot;
//
////	cout << fmt::sprintf("Center: P(%lf,%lf,%lf) Q(%lf,%lf,%lf,%lf)\n",
////		opos.x, opos.y, opos.z, orot.w, orot.x, orot.y, orot.z);
////	cout << fmt::sprintf(" Frame: U(%lf,%lf,%lf) => L(%lf,%lf,%lf)\n",
////		upos.x, upos.y, upos.z, rpos.x, rpos.y, rpos.z);
//
//	return rpos;
	return upos;
}

vec3d_t ReferenceFrame::toAstrocentric(const vec3d_t &lpos, double tjd)
{
//	if (center == nullptr)
//		return lpos;
//
//	vec3d_t opos = center->getGlobalPosition(tjd);
//	quatd_t orot = getOrientation(tjd);
//	vec3d_t rpos = opos + (lpos * orot);
//
////	cout << fmt::sprintf("Center: P(%lf,%lf,%lf) Q(%lf,%lf,%lf,%lf)\n",
////		opos.x, opos.y, opos.z, orot.w, orot.x, orot.y, orot.z);
////	cout << fmt::sprintf(" Frame: L(%lf,%lf,%lf) => U(%lf,%lf,%lf)\n",
////		lpos.x, lpos.y, lpos.z, rpos.x, rpos.y, rpos.z);
//
//	return rpos;
	return lpos;
}


vec3d_t ReferenceFrame::fromUniversal(const vec3d_t &upos, double tjd)
{
//	if (center == nullptr)
//		return upos;
//
//	vec3d_t opos = center->getGlobalPosition(tjd);
//	quatd_t orot = glm::conjugate(getOrientation(tjd));
//	vec3d_t rpos = (opos - upos) * orot;
//
//	cout << fmt::sprintf("Center: P(%lf,%lf,%lf) Q(%lf,%lf,%lf,%lf)\n",
//		opos.x, opos.y, opos.z, orot.w, orot.x, orot.y, orot.z);
//	cout << fmt::sprintf(" Frame: U(%lf,%lf,%lf) => L(%lf,%lf,%lf)\n",
//		upos.x, upos.y, upos.z, rpos.x, rpos.y, rpos.z);
//
//	return rpos;
	return upos;
}

vec3d_t ReferenceFrame::toUniversal(const vec3d_t &lpos, double tjd)
{
//	if (center == nullptr)
//		return lpos;
//
//	vec3d_t opos = center->getGlobalPosition(tjd);
//	quatd_t orot = getOrientation(tjd);
//	vec3d_t rpos = opos + (lpos * orot);
//
//	cout << fmt::sprintf("Center: P(%lf,%lf,%lf) Q(%lf,%lf,%lf,%lf)\n",
//		opos.x, opos.y, opos.z, orot.w, orot.x, orot.y, orot.z);
//	cout << fmt::sprintf(" Frame: L(%lf,%lf,%lf) => U(%lf,%lf,%lf)\n",
//		lpos.x, lpos.y, lpos.z, rpos.x, rpos.y, rpos.z);
//
//	return rpos;
	return lpos;
}


quatd_t ReferenceFrame::fromUniversal(const quatd_t &urot, double tjd)
{
//	if (center == nullptr)
//		return urot;
//	return urot * getOrientation(tjd);
	return urot;
}

quatd_t ReferenceFrame::toUniversal(const quatd_t &lrot, double tjd)
{
//	if (center == nullptr)
//		return lrot;
//	return glm::conjugate(getOrientation(tjd)) * lrot;
	return lrot;
}
