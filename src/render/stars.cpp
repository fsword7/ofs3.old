/*
 * stars.cpp - Scene package - handles star rendering
 *
 *  Created on: May 12, 2020
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "universe/astro.h"
#include "render/scene.h"
#include "render/stars.h"

using namespace ofs::astro;
using namespace ofs::renderer;
using namespace ofs::engine;
using namespace ofs::universe;

void Scene::initStarRenderer()
{
	pgmStar  = gl.getShader("star");
	vbufStar = new VertexBuffer(gl, 1);
	vbufStar->createBuffer(VertexBuffer::VBO, 1);

	fs::path scfname = fs::current_path() / "data/stars/bbr_color_D58.txt";
	starColors = new StarColors();
	starColors->load(scfname);

	starRenderer = new StarRenderer();

	starRenderer->prm  = &prm;
	starRenderer->ctx  = &gl;
	starRenderer->pgm  = pgmStar;
	starRenderer->vbuf = vbufStar;
	starRenderer->starColors = starColors;
	starRenderer->objectList = &objectList;

	starRenderer->pointStarBuffer = new StarVertex(gl);
	starRenderer->glareStarBuffer = new StarVertex(gl);
}

void Scene::initConstellations(const Universe &universe)
{
	const Asterism &constellations = universe.getAsterism();
	const StarCatalog &starlib = universe.getStarCatalog();
	const vector<AsterismEntry *> &asterisms = constellations.getAsterisms();

	pgmAsterism = gl.getShader("line");

	pgmAsterism->use();

	vbufAsterism = new VertexBuffer(gl, 1);
	vbufAsterism->createBuffer(VertexBuffer::VBO, 1);

	for (int idx = 0; idx < asterisms.size(); idx++) {
		AsterismEntry *aster = asterisms[idx];
		asterismLines += aster->hip.size();
	}
}

void Scene::initLightSources()
{
	for (int idx = 0; idx < closeStars.size(); idx++)
	{
		// initialize star surface if star is enough close.
//		closeStars[idx]->initSurface(gl);
	}
}

// ******** StarRenderer ********

void StarRenderer::process(const CelestialStar *star, double dist, double appMag) const
{
	vec3d_t spos, rpos;
	double  srad;
	double  rdist;
	double  objSize;
	double  discSize;
	double  discScale;
	double  alpha, ptSize;
	Color   color;

	// Do nothing if star is too far for z-buffer depth range
	if (dist > starDistanceLimit)
		return;

	// Calculate relative position between star and camera positions.
	spos  = star->getLocalPosition(0) * KM_PER_PC;
	rpos  = spos - viewPosition;
	rdist = glm::length(rpos);

//	if (star->getName() == "Sol") {
//		fmt::fprintf(cout, "Star 1 distance: %lf (max %lf)\n",
//			dist, maxSolarSystemDistance);
//		fmt::fprintf(cout, " Position: (%lf,%lf,%lf) Result: %lf\n",
//			rpos.x, rpos.y, rpos.z, glm::dot(rpos, viewNormal));
//		cout.flush();
//	}

	// Do nothing if star is out of view area (behind me).
	if (glm::dot(rpos, viewNormal) < 0.0)
		return;

	// Calculate apparent size of star in view field
	srad    = star->getGeometryRadius();
	objSize = ((srad / rdist) * 2.0) / pixelSize;

//	if (star->getName() == "Sol") {
//		fmt::fprintf(cout, "Star 2 distance: %lf (max %lf)\n",
//			dist, maxSolarSystemDistance);
//		cout.flush();
//	}

	if (dist < maxSolarSystemDistance) {
		// Add this to object list for z-buffer sorting so that
		// it will not occlude other objects in solar system.
		// Also that will be rendering as sphere and surface if
		// star is very close.

		ObjectListEntry ole;

		mat3d_t view = glm::toMat3(prm->crot);

		ole.type	  = ObjectListEntry::objRenderableStar;
		ole.object	  = star;
		ole.position  = rpos;
		ole.distance  = rdist;
		ole.radius	  = star->getGeometryRadius();
		ole.pixelSize = objSize;
		ole.appMag    = appMag;
		ole.zCenter   = -glm::dot(ole.position, view[2]);
		ole.isOpague  = true;

		objectList->push_back(ole);

	} else {
	//	if (star.getHIPNumber() == 0)
	//		cout << "Sun distance: " << rdist << " size: " << glm::degrees(asin(srad/rdist) * 2.0)
	//			 << " pixel: " << pxSize  << " -> " << srad / (rdist * pxSize) << endl;

		float satLevel = faintestMagnitude - 1.0;
		float alpha    = (faintestMagnitude - appMag); // * brightnessScale + brightnessBias;

		if (useScaledStars == true) {
			// for scaled star rendering

			discSize = 5.0;
			if (alpha > 1.0) {
				discScale = min(pow(2.0, 0.3 * (saturationMagnitude - appMag)), 100.0);
				discSize *= discScale;

//				float glareAlpha = min(0.5f, discScale / 4.0f);
//				color.setAlpha(glareAlpha);
//				glareStarBuffer->addStar(rpos, color, discSize);

				alpha = 1.0;
			} else if (alpha < 0.0)
				alpha = 0.0;

		} else {
			// for point star rendering
			discSize = 1.0;
			if (alpha > 1.0) {
				discScale = min(100.0, satLevel - appMag + 2.0);

//				float glareAlpha = min(0.5f, discScale / 4.0f);
//				color.setAlpha(glareAlpha);
//				glareStarBuffer->addStar(rpos, color, discSize);

			} else if (alpha < 0.0)
				alpha = 0.0;
		}

		color = starColors->lookup(star->getTemperature());
		color.setAlpha(alpha);

		//	if (star.getHIPNumber() == 0) {
		//		cout << "Star size: " << discSize << " Position: " << rpos.x << "," << rpos.y << "," << rpos.z << endl;
		//		cout << "Star color: " << color.getRed() << "," << color.getGreen() << "," << color.getBlue() << "," << color.getAlpha() << endl;
		//		discSize = 20.0;
		////		rpos = -rpos;
		////		starBuffer->addStar(rpos, color, discSize);
		//	}

		//	if (spos == vec3d_t(0, 0, 0))
		//		cout << "HIP " << star.getHIPNumber() << " at origin" << endl;

			// Finally, now display star
		//	cout << "@@@ Adding a star..." << endl;
			pointStarBuffer->addStar(rpos, color, discSize);
	}
}

//void Scene::buildGaussDiscStar(uint32_t log2Size, double scale, double power)
//{
//	uint32_t size = 1u << log2Size;
//	double sigma = scale / 2.3245;
//	double isig2 = 1.0 / (2.0 * sigma * sigma);
//	double s = 1.0 / (sigma * sqrt(PI * 2.0));
//
//	for (uint32_t yidx = 0; yidx < size; yidx++)
//	{
//		double y = double(yidx) - size / 2.0;
//		for (uint32_t xidx = 0; xidx < size; xidx++)
//		{
//			double x = double(xidx) - size / 2.0;
//			auto r2 = x*x + y*y;
//			auto f = s * exp(-r2 * isig2) * power;
//			auto val = min(f, 1.0);
//			cout << fmt::sprintf(" %.6lf", val);
////			data[(yidx * size) + xidx] = uint8_t(255.99 * min(f, 1.0));
//		}
//		cout << endl;
//	}
//}

uint16_t *Scene::buildGaussGlareStar(uint32_t log2Size, double scale, double base)
{
	uint32_t size = 1u << log2Size;
	uint16_t *data = new uint16_t[size * size];

	for (uint32_t yidx = 0; yidx < size; yidx++)
	{
		float y = float(yidx) - size / 2.0f;
		for (uint32_t xidx = 0; xidx < size; xidx++)
		{
			float x = float(xidx) - size / 2.0f;
			auto r = float(sqrt(x*x + y*y));
			auto f = float(pow(base, r * scale));
			auto val = uint16_t(65535.99f * min(f, 1.0f));
//			cout << fmt::sprintf(" %05d", val);
			data[(yidx * size) + xidx] = val;
		}
//		cout << endl;
	}

	return data;
}

void Scene::renderStars(const StarCatalog &stardb, double faintest)
{
	double  fov    = cam->getFOVY();
	double  aspect = cam->getAspect();

	starRenderer->viewPosition = prm.cpos;
	starRenderer->viewNormal = prm.vpnorm;
	starRenderer->faintestMagnitude = faintestMagnitude;
	starRenderer->faintestMagnitudeNight = faintest;
	starRenderer->saturationMagnitude = saturationMagnitude;
	starRenderer->pixelSize = prm.pixelSize;

	// Set MVP for star rendering
	prm.dmProj = glm::perspective(cam->getFOVY(), cam->getAspect(), DIST_NEAR, DIST_FAR);
	prm.dmView = glm::transpose(glm::toMat4(prm.crot));

	// Start star rendering now
	gl.enableBlend();
	starRenderer->pointStarBuffer->start(prm);
	starRenderer->glareStarBuffer->start(prm);
	stardb.findVisibleStars(*starRenderer, prm.cpos, prm.crot, fov, aspect, faintest);
	starRenderer->pointStarBuffer->finish();
	starRenderer->glareStarBuffer->finish();
	gl.disableBlend();
}

void Scene::renderConstellations(const Universe &universe, const Player &player)
{
	const Asterism &constellations = universe.getAsterism();
	const StarCatalog &starlib = universe.getStarCatalog();
	const vector<AsterismEntry *> &asterisms = constellations.getAsterisms();

	Camera *cam = views[0];
	vec3d_t cpos = prm.cpos;
	int cLines = 0;

	VertexLine *vertices = nullptr;
	uint32_t vbo = vbufAsterism->getVBO();

	pgmAsterism->use();
	vbufAsterism->bind();


	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, asterismLines * sizeof(VertexLine), nullptr, GL_STREAM_DRAW);
	vertices = reinterpret_cast<VertexLine *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	if (vertices == nullptr) {
		fmt::fprintf(cerr, "Can't render stars - aborted (error code: %d\n)", glGetError());
		return;
	}

//	for (int idx = 0; idx < asterisms.size(); idx++) {
//		Asterism *aster = asterisms[idx];
//		cLines += aster->hip.size();
//	}
//	if (bufAsterism == nullptr) {
//		bufAsterism = new VertexLine[cLines];
//	}

	int rLines = 0;
	for (int idx = 0; idx < asterisms.size(); idx++) {
		AsterismEntry *aster = asterisms[idx];
		for (int sidx = 0; sidx < aster->hip.size(); sidx += 2) {
			CelestialStar *star1 = starlib.getIndex(aster->hip[sidx]);
			CelestialStar *star2 = starlib.getIndex(aster->hip[sidx+1]);

			if (star1 == nullptr)
				std::cout << "HIP " << aster->hip[sidx] << " Missing" << std::endl;
			if (star2 == nullptr)
				std::cout << "HIP " << aster->hip[sidx+1] << " Missing" << std::endl;
			if (star1 == nullptr || star2 == nullptr)
				continue;

			vertices[rLines].lpos   = vec3f_t((star1->getLocalPosition(0) * KM_PER_PC) - prm.cpos);
			vertices[rLines].color  = Color(0.5, 0.5, 0.5, 1.0);
			rLines++;
			vertices[rLines].lpos   = vec3f_t((star2->getLocalPosition(0) * KM_PER_PC) - prm.cpos);
			vertices[rLines].color  = Color(0.5, 0.5, 0.5, 1.0);
			rLines++;

//			std::cout << "HIP: " << aster->hip[sidx]
//					  << " Name: " << star->name(0) << std::endl;
		}
//		std::cout << std::endl;
	}

	if (!glUnmapBuffer(GL_ARRAY_BUFFER)) {
		cerr << "Buffer corrupted - aborted (error code: " << glGetError() << ")" << endl;
		return;
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLine), (void *)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexLine), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Set MVP for star rendering
	prm.dmProj = glm::perspective(cam->getFOVY(), cam->getAspect(), DIST_NEAR, DIST_FAR);
	prm.dmView = glm::transpose(glm::toMat4(prm.crot));

	mat4f_t mvp = mat4f_t(prm.dmProj * prm.dmView);
	pgmAsterism->setMatrix4fv("mvp", mvp);

	glDrawArrays(GL_LINES, 0, rLines);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	vbufAsterism->unbind();

	glUseProgram(0);
}
