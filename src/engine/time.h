/*
 * time.h - time handler package
 *
 *  Created on: Jun 6, 2020
 *      Author: Tim Stark
 */

#pragma once

#define DAYS_PER_YEAR		365.25
#define HOURS_PER_HOUR		24.0
#define MINUTES_PER_DAY		1440.0
#define SECONDS_PER_DAY		86400.0

class Time
{
public:
	Time();
	Time(int y, int m, int d);
	Time(double);

	void reset();

private:
	// Julian time
	double lastTime = 0;
	double sysTime = 0;
	double julianTime = 0;

};
