/*
 * starcolors.cpp - Stellar color temperature database package
 *
 *  Created on: Jul 28, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "util/color.h"
#include "render/starcolors.h"

using namespace ofs::renderer;

bool StarColors::load(const fs::path &fname)
{
	std::ifstream  data(fname.c_str(), std::ios::in);
	std::string    line;
	int            lineno;
	Color          color;
	int            temp;
	float          r, g, b;

	if (!data.is_open())
	{
		fmt::fprintf(cerr, "OFS: I/O error: file '%s': %s\n",
			fname.filename().string(), strerror(errno));
		return false;
	}

	lineno = 0;
//	cname = 0;
	while (std::getline(data, line))
	{
		std::stringstream lineStream(line);
		std::string       cell;
		std::vector<std::string> cells;

		if (lineno++ == 0)
			continue;
		if (line.size() == 0)
			continue;
		if (line.c_str()[0] == '#')
			continue;

		cells.clear();
		while(!lineStream.eof()) {
			std::string tmp;
			lineStream >> tmp;
			cells.push_back(tmp);
		}
		if (cells.size() != D58_nSIZE)
			continue;

//		std::cout << "Color: ";
//		for (int idx = 0; idx < cells.size(); idx++) {
//			std::cout << cells[idx] << ",";
//		}
//		std::cout << std::endl;

		sscanf(cells[D58_nTEMP].c_str(), "%d", &temp);
		sscanf(cells[D58_nFRED].c_str(), "%f", &r);
		sscanf(cells[D58_nFGREEN].c_str(), "%f", &g);
		sscanf(cells[D58_nFBLUE].c_str(), "%f", &b);

//		if (cells[D58_nCMF] == "10deg")
//			std::cout << "Temp: " << temp << " (" << r << "," << g << "," << b << ")" << std::endl;

		color = Color(r, g, b);
		if (cells[D58_nCMF] == "2deg") {
			colors2.push_back(color);
			temps.push_back(temp);
		}
		if (cells[D58_nCMF] == "10deg")
			colors10.push_back(color);
	}
	minTemp   = temps[0];
	maxTemp   = temps[temps.size()-1];
	tempScale = (maxTemp - minTemp) / (temps.size()-1);

	fmt::fprintf(cout, "Total %d black body colors (2deg).\n", colors2.size());
	fmt::fprintf(cout, "Total %d black body colors (10deg).\n", colors10.size());
	fmt::fprintf(cout, "Range temperature: %d to %d (scale: %lf)\n",
		minTemp, maxTemp, tempScale);

	data.close();
	return true;
}

Color StarColors::lookup(int temp) const
{
	Color color;

	if (temp < minTemp)
		return Color(0, 0, 0);
	if (temp > maxTemp)
		return colors2[colors2.size()-1];
	return colors2[(temp - minTemp) / tempScale];
}



