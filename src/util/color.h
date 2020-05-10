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
	Color(float red, float green, float blue, float alpha = 1.0)
	: red(red), green(green), blue(blue), alpha(alpha)
	{}

public:
	float red   = 0.0;
	float green = 0.0;
	float blue  = 0.0;
	float alpha = 1.0;
};
