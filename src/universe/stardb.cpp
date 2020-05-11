/*
 * stardb.cpp - Star catalog database package
 *
 *  Created on: May 11, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "universe/object.h"
#include "universe/stardb.h"
#include "universe/universe.h"

using namespace ofs::universe;

bool StarCatalog::loadXHIPData(fs::path dataFolder)
{

	fs::path mfname = dataFolder / "stars/xhip/main.dat";
	fs::path pfname = dataFolder / "stars/xhip/photo.dat";
	fs::path bfname = dataFolder / "stars/xhip/biblio.dat";
	fs::path gfname = dataFolder / "stars/xhip/groups.dat";

	ifstream mdata(mfname.c_str(), ios::in);
	ifstream pdata(pfname.c_str(), ios::in);
	ifstream bdata(bfname.c_str(), ios::in);
//	ifstream gdata(gfname.c_str(), ios::in);

	std::string mline, pline, bline;
	int    lineno;
	int    hip, phip, bhip;
	int    hd;
	double ra, de, plx, eplx, dist, edist;
    double bMag, vMag, ci, lum;
	int    cnplx, czplx;
    char   spType[26];
    CelestialStar *star;

    if (!mdata.is_open())
	{
		std::cerr << "I/O Error: file '" << mfname << "': "
				  << std::strerror(errno) << std::endl;
		return false;
	}

	if (!pdata.is_open())
	{
		std::cerr << "I/O Error: file '" << pfname << "': "
				  << std::strerror(errno) << std::endl;
		mdata.close();
		return false;
	}

	if (!bdata.is_open())
	{
		std::cerr << "I/O Error: file '" << bfname << "': "
				  << std::strerror(errno) << std::endl;
		mdata.close();
		pdata.close();
		return false;
	}

    // Create the Sun (Sol)
//	star = CelestialStar::createSun();
//	uStars.push_back(star);

	lineno = 0;
	cnplx = 0;
	czplx = 0;
//	cname = 0;
	while (std::getline(mdata, mline) &&
		   std::getline(pdata, pline) &&
		   std::getline(bdata, bline))
	{
		std::stringstream mlStream(mline);
		std::stringstream plStream(pline);
		std::stringstream blStream(bline);

		std::string       cell;
		std::vector<std::string> mcells, pcells, bcells;

		lineno++;

		mcells.clear();
		pcells.clear();
		bcells.clear();
		while(std::getline(mlStream, cell, '|'))
			mcells.push_back(cell);
		while(std::getline(plStream, cell, '|'))
			pcells.push_back(cell);
		while(std::getline(blStream, cell, '|'))
			bcells.push_back(cell);

//		if (lineno < 100)
//			for (uint32_t idx = 0; idx < cells.size(); idx++)
//				std::cout << cells[idx] << ((idx < cells.size() - 1) ? "," : "\n");

//		if (!cells[HYG3_nNAME].empty()) {
//			std::cout << "HYG " << cells[HYG3_nID] << ": " << cells[HYG3_nNAME] << std::endl;
//			cname++;
//		}

		sscanf(mcells[XHIP_M_nHIP].c_str(), "%d", &hip);
		sscanf(pcells[XHIP_P_nHIP].c_str(), "%d", &phip);
		sscanf(bcells[XHIP_B_nHIP].c_str(), "%d", &bhip);
//		if (hip != phip || hip != bhip)
//			continue;
		if (hip != phip || hip != bhip) {
			cout << "HIP " << hip << " != " << phip << endl;
			break;
		}

		sscanf(mcells[XHIP_M_nRADEG].c_str(), "%lf", &ra);
		sscanf(mcells[XHIP_M_nDEDEG].c_str(), "%lf", &de);
		sscanf(mcells[XHIP_M_nPLX].c_str(), "%lf", &plx);
//		sscanf(mcells[XHIP_M_nDIST].c_str(), "%lf", &dist);
        sscanf(mcells[XHIP_M_nSPTYPE].c_str(), "%s", spType);

        sscanf(pcells[XHIP_P_nVAPPMAG].c_str(), "%lf", &vMag);
        if (sscanf(pcells[XHIP_P_nBAPPMAG].c_str(), "%lf", &bMag) != 1)
            bMag = vMag;
        ci = bMag - vMag;

//		sscanf(pcells[XHIP_P_nBV].c_str(), "%lf", &ci);
		sscanf(pcells[XHIP_P_nLUM].c_str(), "%lf", &lum);

		if (plx < 0) {
			cnplx++;
//			std::cout << "ID: " << hip << " RA: " << ra << " DEC: " << de << " PLX: " << plx << std::endl;
            dist = 100000;
		} else if (plx == 0.0) {
			czplx++;
//			std::cout << "ID: " << hip << " RA: " << ra << " DEC: " << de << " PLX: " << plx << std::endl;
            dist = 100000;
		} else {
//			sscanf(mcells[XHIP_M_nEPLX].c_str(), "%lf", &eplx);
			dist  = 1000.0/plx;
//			edist = 1000.0/plx * (1 + 1.2*(eplx/plx)*(eplx/plx));
//			std::cout << "ID: " << hip << " PLX: " << plx << " ePLX: " << eplx
//					  << " Dist: " << dist << " eDist: " << edist << std::endl;
		}

//		star = CelestialStar::create(ra, de, dist, spType, vMag, ci, lum);
//		star->setHIPNumber(hip);
//		star->setName(bcells[XHIP_B_nNAME]);

//		uStars.push_back(star);

//		if (glm::length(star->getPosition(0)) < 1.0) {
//			vec3d_t pos = star->getPosition(0);
//			cout << "HIP " << hip << " Position: " << setprecision(16) << fixed << pos.x << "," << pos.y << "," << pos.z
//				 << " From origin: " << glm::length(pos) << endl;
//		}
	}

	mdata.close();
	pdata.close();
	bdata.close();
//	gdata.close();

	cout << "Total " << cnplx << " stars with negative parallax." << endl;
	cout << "Total " << czplx << " stars with zero parallax." << endl;

//    finish();

	return true;
}
