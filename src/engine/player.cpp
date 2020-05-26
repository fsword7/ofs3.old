/*
 * player.cpp - player control interface package
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/player.h"

using namespace ofs::engine;

void Player::setAngularVelocity(vec3d_t _av)
{
	av = _av;
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
	upos = lpos;
	urot = lrot;
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
