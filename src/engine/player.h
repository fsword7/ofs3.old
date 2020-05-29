/*
 * player.h - player control interface package
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "engine/object.h"

namespace ofs::engine
{
	class PlayerFrame
	{
	public:
		enum FrameType {
			frameEcliptic,
			frameEquatorial,
			frameFrontHelioSync,
			frameBackHelioSync,
			frameObjectSync
		};

		PlayerFrame() = default;
		~PlayerFrame() = default;

	private:
		FrameType  type = frameEcliptic;
	};

	class Player // : public Object
	{
	public:
		enum TravelMode {
			tvFree
		};

//		Player() : Object("(Player)", objPlayer) {}
		Player() = default;
		~Player() = default;

		// Getters
		inline double  getCurrentTime() const { return nowTime; }
		inline double  getRealTime() const { return realTime; }

		inline vec3d_t getGlobalPosition() const { return upos; }
		inline quatd_t getGlobalOrientation() const { return urot; }

		inline vec3d_t getLocalPosition() const { return lpos; }
		inline quatd_t getLocalOrientation() const { return lrot; }

		inline vec3d_t getAngularVelocity() { return av; }
		inline vec3d_t getTravelVelocity()  { return tv; }
		inline double  getTravelSpeed()     { return tv.z; }

		inline Object *getSelectedObject() const { return selectedObject; }

		// Setters
		inline void setCurrentTime(double t) { nowTime = t; }
		inline void setRealTime(double t)    { realTime = t; }

		void setAngularVelocity(vec3d_t av);
		void setTravelVelocity(vec3d_t tv);
		void setTravelSpeed(double ts);

		void updateUniversal();
		void update(double dt);

		void move(const Object &obj, double dist = 0);
		void follow(const Object &obj);
		void look(const Object &obj);

	private:
		PlayerFrame frame;

		Object *selectedObject = nullptr;

		TravelMode mode = tvFree;

		double  nowTime = 0;  // Current simulation time
		double  realTime = 0; // Current real time (today)

		// Global position (universe coordinate system)
		vec3d_t upos = { 0.0, 0.0, 0.0 };
		quatd_t urot = { 1.0, 0.0, 0.0, 0.0 };

		// Local position { local coordinate system in reference frame )
		vec3d_t lpos = { 0.0, 0.0, 0.0 };
		quatd_t lrot = { 1.0, 0.0, 0.0, 0.0 };

		// Velocity control
		vec3d_t	av = { 0.0, 0.0, 0.0 };      // Angular velocity
		quatd_t wv = { 1.0, 0.0, 0.0, 0.0 }; //    Quaternion control
		vec3d_t	tv = { 0.0, 0.0, 0.0 };      // Travel velocity
	};
}
