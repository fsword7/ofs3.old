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
			frameUniversal,
			frameEcliptical,
			frameEquatorial,
			frameFrontHelioSync,
			frameBackHelioSync,
			frameObjectSync
		};

		PlayerFrame() = default;
		~PlayerFrame();

		void set(FrameType type, const Object *object, const Object *target);

		const Object *getCenter() const;

		vec3d_t fromUniversal(const vec3d_t &pos, double now);
		quatd_t fromUniversal(const quatd_t &rot, double now);
		vec3d_t toUniversal(const vec3d_t &pos, double now);
		quatd_t toUniversal(const quatd_t &rot, double now);

	private:
		FrameType  type = frameUniversal;
		Frame     *frame = nullptr;
	};

	class Player // : public Object
	{
	public:
		enum TravelMode {
			tvFree
		};

		enum FollowMode {
			fwEcliptic,
			fwGeoSync,
			fwHelioSync,
			fwObjectSync
		};

		enum GoMode {
			goEcliptic,
			goGeoSync,
			goFrontHelioSync,
			goBackHelioSync,
			goObjectSync
		};

		Player();
		~Player();

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

		void move(const Object &obj, GoMode mode, double dist = 0);
		void follow(const Object &obj, FollowMode mode);
		void look(const Object &obj);

		void rotate(quatd_t rot);
		void orbit(quatd_t rot);
		void dolly(double delta);

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
		vec3d_t lpos   = { 0.0, 0.0, 0.0 };
		quatd_t lrot   = { 1.0, 0.0, 0.0, 0.0 };
		quatd_t lorbit = { 1.0, 0.0, 0.0, 0.0 };

		// Velocity control
		vec3d_t	pav = { 0.0, 0.0, 0.0 };      // Player angular velocity
		quatd_t pwv = { 1.0, 0.0, 0.0, 0.0 }; //    Quaternion control
		vec3d_t oav = { 0.0, 0.0, 0.0 };      // Orbital angular velocity
		quatd_t owv = { 1.0, 0.0, 0.0, 0.0 }; //    Quaternion control
		vec3d_t	tv  = { 0.0, 0.0, 0.0 };      // Travel velocity
	};
}
