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

		void set(FrameType type, const Object *object, const Object *target);

	private:
		FrameType  type = frameEcliptic;
		ReferenceFrame *frame = nullptr;
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

		inline vec3d_t getPlayerAngularVelocity()  { return pav; }
		inline vec3d_t getOrbitalAngularVelocity() { return oav; }
		inline vec3d_t getTravelVelocity()         { return tv; }
		inline double  getTravelSpeed()            { return tv.z; }

		inline Object *getSelectedObject() const { return selectedObject; }

		// Setters
		inline void setCurrentTime(double t) { nowTime = t; }
		inline void setRealTime(double t)    { realTime = t; }

		void setPlayerAngularVelocity(vec3d_t av);
		void setOrbitalAngularVelocity(vec3d_t av);
		void setTravelVelocity(vec3d_t tv);
		void setTravelSpeed(double ts);

		void setSelectedObject(Object *obj) { selectedObject = obj; }

		void updateUniversal();
		void update(double dt);

		void setFrame(PlayerFrame::FrameType type, const Object *object,
			const Object *target);

		void move(const Object &obj, double dist = 0);
		void follow(const Object &obj);
		void look(const Object &obj);

		void orbit(quatd_t rot);

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
		vec3d_t	pav = { 0.0, 0.0, 0.0 };      // Player angular velocity
		quatd_t pwv = { 1.0, 0.0, 0.0, 0.0 }; //    Quaternion control
		vec3d_t oav = { 0.0, 0.0, 0.0 };      // Orbital angular velocity
		quatd_t owv = { 1.0, 0.0, 0.0, 0.0 }; //    Quaternion control
		vec3d_t	tv  = { 0.0, 0.0, 0.0 };      // Travel velocity
	};
}
