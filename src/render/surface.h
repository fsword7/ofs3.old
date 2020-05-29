/*
 * surface.h - OFS terrain surface package
 *
 *  Created on: May 10, 2020
 *      Author: Tim Stark
 */

#pragma once

namespace ofs::renderer
{
	class Surface {
	public:
		Surface() = default;
		~Surface() = default;

		void createSphere(int level, int ilat, int ilng, int xGrids, int yGrids);

	private:
		Color defaultColor;

	};
}
