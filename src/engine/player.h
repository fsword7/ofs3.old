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

	private:
		PlayerFrame frame;

	};
}
