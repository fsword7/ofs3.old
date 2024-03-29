/*
 * color.h - SDR/HDR color package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#pragma once

class Color
{
public:
	Color() = default;
	Color(float red, float green, float blue, float alpha = 1.0)
	: red(red), green(green), blue(blue), alpha(alpha)
	{}

	inline void setRed(float r)   { red = r; }
	inline void setGreen(float g) { green = g; }
	inline void setBlue(float b)  { blue = b; }
	inline void setAlpha(float a) { alpha = a; }

public:
	float red   = 0.0;
	float green = 0.0;
	float blue  = 0.0;
	float alpha = 1.0;
};
