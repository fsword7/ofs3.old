/*
 * frame.h - reference frame package
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#pragma once

namespace ofs::engine
{
	class Object;

	class ReferenceFrame
	{
	public:
		ReferenceFrame() = default;
		virtual ~ReferenceFrame() = default;

		inline bool isRoot() const       { return parent == nullptr; }
		inline Object *getCenter() const { return center; }

		vec3d_t fromAstrocentric(const vec3d_t &pos, double now);
		vec3d_t toAstrocentric(const vec3d_t &pos, double now);

		vec3d_t fromUniversal(const vec3d_t &pos, double now);
		quatd_t fromUniversal(const quatd_t &rot, double now);
		vec3d_t toUniversal(const vec3d_t &pos, double now);
		quatd_t toUniversal(const quatd_t &rot, double now);

	protected:
		ReferenceFrame *parent = nullptr;
		Object         *center = nullptr;
	};

	class CachingFrame : public ReferenceFrame
	{
	public:
		CachingFrame() = default;
		~CachingFrame() = default;

	private:
	};
}
