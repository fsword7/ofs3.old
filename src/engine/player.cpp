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

PlayerFrame::~PlayerFrame()
{
	if (frame != nullptr)
		frame->release();
}

void PlayerFrame::set(FrameType type, const Object *object, const Object *target)
{
	this->type = type;

	if (frame != nullptr)
		frame->release();

	switch (type)
	{
	case frameUniversal:
		frame = nullptr;
		break;
	case frameEcliptical:
		frame = new J2000EclipticFrame(object);
		break;
	}
}

const Object *PlayerFrame::getCenter() const
{
	if (frame == nullptr)
		return nullptr;
	return frame->getCenter();
}

vec3d_t PlayerFrame::fromUniversal(const vec3d_t &pos, double now)
{
	if (frame == nullptr)
		return pos;
	return frame->fromUniversal(pos, now);
}

quatd_t PlayerFrame::fromUniversal(const quatd_t &rot, double now)
{
	if (frame == nullptr)
		return rot;
	return frame->fromUniversal(rot, now);
}

vec3d_t PlayerFrame::toUniversal(const vec3d_t &pos, double now)
{
	if (frame == nullptr)
		return pos;
	return frame->toUniversal(pos, now);
}

quatd_t PlayerFrame::toUniversal(const quatd_t &rot, double now)
{
	if (frame == nullptr)
		return rot;
	return frame->toUniversal(rot, now);
}

// ******** Player ********

Player::Player()
// : Object("(Player)", objPlayer) {}
{
	frame.set(PlayerFrame::frameUniversal, nullptr, nullptr);
}

Player::~Player()
{
}

void Player::setAngularVelocity(vec3d_t vel)
{
	av = vel;
	wv = quatd_t(0, av.x, av.y, av.z);
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
	upos = frame.toUniversal(lpos, nowTime);
	urot = frame.toUniversal(lrot, nowTime);
}

void Player::setFrame(PlayerFrame::FrameType type, const Object *object,
	const Object *target)
{
	frame.set(type, object, target);

	// Reset local position and orientation
	lpos = frame.fromUniversal(upos, nowTime);
	lrot = frame.fromUniversal(urot, nowTime);
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
		lrot += lrot * wv * (dt / 2.0);
		lrot  = glm::normalize(lrot);
		lpos -= lrot * tv * dt;
	}

	// Updating current universal coordinates
	updateUniversal();
}

void Player::move(const Object &obj, GoMode mode, double dist)
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
	lpos = frame.fromUniversal(upos, nowTime);
	lrot = frame.fromUniversal(urot, nowTime);
}

void Player::follow(const Object &obj, FollowMode mode)
{
	switch(mode)
	{
	case fwEcliptic:
	default:
		frame.set(PlayerFrame::frameEcliptical, &obj, nullptr);
		break;
	}
}

void Player::look(const Object &obj)
{

	vec3d_t opos = obj.getGlobalPosition(nowTime);
	vec3d_t up   = vec3d_t(0, 1, 0);

	urot = glm::lookAt(upos, opos, up);
	lrot = frame.fromUniversal(urot, nowTime);
}

void Player::dolly(double delta)
{
	const Object *center = frame.getCenter();
	if (center == nullptr)
		return;

	double radius = center->getGeometryRadius();
	double dist   = glm::length(lpos);
	double cdist  = dist - radius;
	if (cdist < 0)
		cdist = 0;

	double ndist = exp(log(cdist) + delta);
	lpos *= (ndist / cdist);

	updateUniversal();
}

void Player::rotate(quatd_t rot)
{
	lpos = lpos * rot;

	updateUniversal();
}

void Player::orbit(quatd_t rot)
{
	if (frame.getCenter() == nullptr)
		return;

	quatd_t qrot = glm::normalize(lrot * rot * glm::conjugate(lrot));

	lpos = glm::normalize(glm::conjugate(qrot) * lpos) * glm::length(lpos);
	lrot = glm::conjugate(qrot) * lrot;

	updateUniversal();
}
