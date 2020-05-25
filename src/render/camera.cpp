/*
 * camera.cpp - Camera/View package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/camera.h"

using namespace ofs::renderer;

Camera::Camera(ViewType type)
: viewType(type)
{

}

void Camera::resize(int _width, int _height)
{
	width  = _width;
	height = _height;
	aspect = double(width)/double(height);
}

double Camera::computePixelSize() const
{
	return 2.0 * tan(fovY / 2.0) / double(height);
}
