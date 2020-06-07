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

	class Frame
	{
	public:
		Frame(const Object *object, const Frame *parent = nullptr);
	protected:
		virtual ~Frame() = default;

	public:
		int lock() const;
		int release() const;

		inline bool isRoot() const                 { return parent == nullptr; }
		inline const Object *getCenter() const     { return center; }
		inline const Frame *getParentFrame() const { return parent; }
		inline string getFrameName() const         { return frameName; }

		virtual quatd_t getOrientation(double now) const = 0;

		vec3d_t fromAstrocentric(const vec3d_t &pos, double now);
		vec3d_t toAstrocentric(const vec3d_t &pos, double now);

		vec3d_t fromUniversal(const vec3d_t &pos, double now);
		quatd_t fromUniversal(const quatd_t &rot, double now);
		vec3d_t toUniversal(const vec3d_t &pos, double now);
		quatd_t toUniversal(const quatd_t &rot, double now);

	protected:
		const Frame  *parent   = nullptr;
		const Object *center   = nullptr;
		string        frameName;

	private:
		mutable int refCount = 0;
	};

	using ReferenceFrame = Frame;

	class CachingFrame : public ReferenceFrame
	{
	public:
		CachingFrame() = default;
		~CachingFrame() = default;

	private:
	};

	class J2000EclipticFrame : public ReferenceFrame
	{
	public:
		J2000EclipticFrame(const Object *obj, const Frame *parent = nullptr);
		~J2000EclipticFrame() = default;

		quatd_t getOrientation(double) const override
		{
			return quatd_t(1,0,0,0);
		}
	};
}
