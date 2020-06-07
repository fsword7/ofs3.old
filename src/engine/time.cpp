/*
 * time.cpp - time handler package
 *
 *  Created on: Jun 6, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/time.h"

static const char *shortMonthList[] =
{
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static const char *fullMonthList[] =
{
		"January", "February", "March",     "April",   "May",      "June",
		"July",    "August",   "September", "October", "November", "December"
};

Time::Time()
{
}

Time::Time(int y, int m, int d)
{
}

Time::Time(double)
{
}

void Time::reset()
{
	using clk = chrono::high_resolution_clock;

	auto now = clk::now();

//	struct timeval now;
//
//	gettimeofday(&now, nullptr);
//	sysTime = double(now.tv_sec) + (double(now.tv_usec) / 1.0e6);
//	lastTime = sysTime;
}
