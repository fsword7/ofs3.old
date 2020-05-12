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
