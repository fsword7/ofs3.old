/*
 * coreapp.h - core application package
 *
 *  Created on: May 24, 2020
 *      Author: Tim Stark
 */

#pragma once

#include "engine/engine.h"

namespace ofs
{
	using Engine = ofs::engine::Engine;
	using Player = ofs::engine::Player;

	class CoreApp
	{
	public:
		enum mouseButton {
			mouseLeftButton   = 0x01,
			mouseMiddleButton = 0x02,
			mouseRightButton  = 0x04
		};

		enum keyControlCode {
			keyShift       = 0x10,
			keyControl     = 0x20,
			keyAlternate   = 0x40
		};

		enum keyCode {
			keyUndefined	= 0x000,

			// 0x01-0xFF reserved for ASCII codes

			keyF0		= 0x100,
			keyF1		= 0x101,
			keyF2		= 0x102,
			keyF3		= 0x103,
			keyF4		= 0x104,
			keyF5		= 0x105,
			keyF6		= 0x106,
			keyF7		= 0x107,
			keyF8		= 0x108,
			keyF9		= 0x109,
			keyF10		= 0x10A,
			keyF11		= 0x10B,
			keyF12		= 0x10C,

			keyPad0		= 0x120,
			keyPad1		= 0x121,
			keyPad2		= 0x122,
			keyPad3		= 0x123,
			keyPad4		= 0x124,
			keyPad5		= 0x125,
			keyPad6		= 0x126,
			keyPad7		= 0x127,
			keyPad8		= 0x128,
			keyPad9		= 0x129,

			keyUp		= 0x130,
			keyDown		= 0x131,
			keyLeft		= 0x132,
			keyRight	= 0x133,
			keyHome		= 0x134,
			keyEnd		= 0x135,
			keyPageUp	= 0x136,
			keyPageDown	= 0x137,
			keyInsert	= 0x138,
			keyDelete	= 0x139
		};

		CoreApp() = default;
		virtual ~CoreApp() = default;

		void initEngine();

		virtual void init();
		virtual void clean();
		virtual void update();
		virtual void render();
		virtual void resize(uint32_t width, uint32_t height);

		virtual void initScreen() = 0;
		virtual void closeScreen() = 0;
		virtual void display(const string &title) = 0;
		virtual void run() = 0;

		// Mouse controls
		void mouseMove(float x, float y, int state);
		void mousePressButtonDown(float x, float y, int state);
		void mousePressButtonUp(float x, float y, int state);
		void mouseDialWheel(float motion, int state = 0);

		// Keyboard controls
		void keyPress(keyCode code, int modifiers, bool down);
//		void keyDown(keyCode code, int modifiers);
//		void keyUp(keyCode code, int modifiers);
		void keyEntered(char32_t ch, int modifiers);

	private:
		Engine *engine = nullptr;

		// keyboard handle parameters
		bool	stateKey[512];
		double	keyRotationAccel;
		double	keyRotationBrake;
		double	keyTravelAccel;
		double	keyTravelBrake;

		// Current screen dimsension
		uint32_t width = 1;
		uint32_t height = 1;

		// mouse handle parameters
		float lastX, lastY;
	};
}
