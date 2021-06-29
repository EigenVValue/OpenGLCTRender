#ifndef DCMTOMODEL_H_INCLUDED
#define DCMTOMODEL_H_INCLUDED

#include "dualmc.h"
#include "dependencies/include/glm/glm.hpp"

class dcmToModel {
public:
	void run(
		const std::vector<uint8_t> raw,
		unsigned int &dimX,
		unsigned int &dimY,
		unsigned int &dimZ,
		const float iso,
		std::vector<glm::vec3> & objVertices,
		std::vector<unsigned int> & objFaces,
		std::vector<uint8_t> & objColors
	);

	// Volume for saving raw data
	struct Volume {
		int32_t dimX;
		int32_t dimY;
		int32_t dimZ;
		float iso;
		std::vector<uint8_t> data;
	};

private:
	void computeSurface(
		Volume volume,
		std::vector<dualmc::Vertex> &vertices,
		std::vector<dualmc::Quad> &quads,
		std::vector<uint8_t> & colors
	);
};

#endif //DCMTOMODEL_H_INCLUDED