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

#include "util/color.h"

using namespace std;

namespace fs = std::filesystem;

// Math library package

#define PI (3.14159265358979323846)

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
