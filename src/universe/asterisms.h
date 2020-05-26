/*
 * asterisms.h - Constellation database package
 *
 *  Created on: Jul 29, 2019
 *      Author: Tim Stark
 */

#pragma once

namespace ofs::universe
{
	struct AsterismEntry {
		string shortName;
		string fullName;
		int nLines;
		vector<int> hip;
	};

	class Asterism
	{
	public:
		Asterism() = default;
		~Asterism() = default;

		bool load(const fs::path &fname);

		const vector<AsterismEntry *> &getAsterisms() const { return asterisms; }

	private:
		vector<AsterismEntry *> asterisms;
	};
}
