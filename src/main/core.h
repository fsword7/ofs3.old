/*
 * core.h - OFS core package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>

#include <fmt/printf.h>

#include "util/color.h"

using namespace std;

namespace fs = std::filesystem;

#define OFS_FULL_NAME		"Orbital Flight Simulator"
#define OFS_SHORT_NAME		"OFS"
#define OFS_DEFAULT_WIDTH	1600
#define OFS_DEFAULT_HEIGHT	1000
#define OFS_DEFAULT_FOV		35.0

// Math library package

#define PI  (3.14159265358979323846)
#define PI2 (PI * 2.0)

#include <cmath>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>

typedef glm::tvec2<float> vec2f_t;
typedef glm::tvec3<float> vec3f_t;
typedef glm::tvec4<float> vec4f_t;
typedef glm::tquat<float> quatf_t;

typedef glm::fmat3 mat3f_t;
typedef glm::fmat4 mat4f_t;

typedef glm::tvec2<double> vec2d_t;
typedef glm::tvec3<double> vec3d_t;
typedef glm::tvec4<double> vec4d_t;
typedef glm::tquat<double> quatd_t;

typedef glm::dmat3 mat3d_t;
typedef glm::dmat4 mat4d_t;

template <typename T> T square(T x) { return x * x; }
template <typename T> T cube(T x)   { return x * x * x; }


// Four CC values for magic codes
inline uint32_t FOURCC(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
    return ( (uint32_t) (((d)<<24) | (uint32_t(c)<<16) | (uint32_t(b)<<8) | uint32_t(a)) );
}

inline uint32_t getFourCC(const char *code)
{
    return ((uint32_t)code[3] << 24) |
           ((uint32_t)code[2] << 16) |
           ((uint32_t)code[1] << 8)  |
           ((uint32_t)code[0]);
}

inline char *strFourCC(uint32_t code)
{
	static char str[5];

	str[0] = char(code >> 24);
	str[1] = char(code >> 16);
	str[2] = char(code >> 8);
	str[3] = char(code);
	str[4] = '\n';

	return str;
}

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define checkAllFlags(flags, mask) ((flags & (mask)) == (mask))
#define checkAnyFlags(flags, mask) (flags & (mask))
