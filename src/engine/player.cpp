/*
 * player.cpp - player control interface package
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/player.h"

using namespace ofs::engine;

// ******** PlayerFrame ********

void PlayerFrame::set(FrameType type, const Object *object, const Object *target)
{
	this->type = type;
}

// ******** Player ********

void Player::setPlayerAngularVelocity(vec3d_t av)
{
	pav = av;
	pwv = quatd_t(0, pav.x, pav.y, pav.z);
}

void Player::setOrbitalAngularVelocity(vec3d_t av)
{
	oav = av;
	owv = quatd_t(0, oav.x, oav.y, oav.z);
}

void Player::setTravelVelocity(vec3d_t _tv)
{
	tv = _tv;
}

void Player::setTravelSpeed(double ts)
{
	tv.z = ts;
}

void Player::updateUniversal()
{
	upos = lpos; // frame.toGlobalSpace(lpos, nowTime);
	urot = lrot; // frame.toGlobalSpace(lrot, nowTime);
}

void Player::setFrame(PlayerFrame::FrameType type, const Object *object,
	const Object *target)
{
	frame.set(type, object, target);

	// Reset local position and orientation
	lpos = upos; // frame.fromGlobalSpace(upos, nowTime);
	lrot = urot; // frame.fromGlobalSpace(urot, nowTime);
}

void Player::update(double dt)
{
	if (mode == tvFree) {
		// Free travel mode
		// Update current position and orientation (local reference frame)
		// Applying angular velocity to rotation quaternion in local space.
		//
		//      dq/dt = q * w * t/2
		//		w = (0, x, y, z)
		//
		lrot += lrot * pwv * (dt / 2.0);
		lrot  = glm::normalize(lrot);
		lpos -= lrot * tv * dt;
	}

	// Updating current universal coordinates
	updateUniversal();
}

void Player::move(const Object &obj, double dist)
{
	vec3d_t opos = obj.getGlobalPosition(nowTime);
	vec3d_t tpos;
	quatd_t orot;

	orot = obj.getOrientation(nowTime);
	if (dist <= obj.getGeometryRadius())
		dist = obj.getGeometryRadius() * 6.0;

	upos = opos + glm::conjugate(orot) * vec3d_t(0, 0, dist);
	urot = orot;

	// Convert global coordinates to local coordinates.
	lpos = upos; // frame->fromGlobalSpace(upos, nowTime);
	lrot = urot; // frame->fromGlobalSpace(urot, nowTime);
}

void Player::follow(const Object &obj)
{

}

void Player::look(const Object &obj)
{

	vec3d_t opos = obj.getGlobalPosition(nowTime);
	vec3d_t up   = vec3d_t(0, 1, 0);

	urot = glm::lookAt(upos, opos, up);
	lrot = urot; // frame->fromGlobalSpace(urot, nowTime);
}

void Player::orbit(quatd_t rot)
{
	const Object *center = nullptr;
	if (center == nullptr)
		return;

	double dist  = glm::length(lpos);
	quatd_t qrot = glm::normalize(lrot * rot * glm::conjugate(lrot));

	lpos = glm::normalize(glm::conjugate(qrot) * lpos) * dist;
	lrot = glm::conjugate(qrot) * lrot;

	updateUniversal();
}
