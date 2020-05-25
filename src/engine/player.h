/*
 * player.h - player control interface package
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#pragma once

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
		FrameType type = frameEcliptic;
	};

	class Player
	{
	public:
		Player() = default;
		~Player() = default;

		// Getters
		inline double  getCurrentTime() const { return nowTime; }
		inline double  getRealTime() const { return realTime; }

		inline vec3d_t getGlobalPosition() const { return upos; }
		inline quatd_t getGlobalOrientation() const { return urot; }

		inline vec3d_t getLocalPosition() const { return lpos; }
		inline quatd_t getLocalOrientation() const { return lrot; }

		// Setters
		inline void setCurrentTime(double t) { nowTime = t; }
		inline void setRealTime(double t)    { realTime = t; }

	private:
		PlayerFrame frame;

		double  nowTime = 0;  // Current simulation time
		double  realTime = 0; // Current real time (today)

		// Global position (universe coordinate system)
		vec3d_t upos = { 0.0, 0.0, 0.0 };
		quatd_t urot = { 1.0, 0.0, 0.0, 0.0 };

		// Local position { local coordinate system in reference frame )
		vec3d_t lpos = { 0.0, 0.0, 0.0 };
		quatd_t lrot = { 1.0, 0.0, 0.0, 0.0 };
	};
}
