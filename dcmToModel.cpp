// Include standard liabraries
#include <vector>

// Dual mc builder
#include "dualmc.h"
#include "dualmc.hpp"

// GLM
#include "dependencies/include/glm/glm.hpp"

#include "dcmToModel.hpp"

void dcmToModel::run(
	const std::vector<uint8_t> raw,
	unsigned int &dimX,
	unsigned int &dimY,
	unsigned int &dimZ,
	const float iso,
	std::vector<glm::vec3> & objVertices,
	std::vector<unsigned int> & objFaces
) {
	// Set volume
	Volume volume;
	// Load raw file
	volume.dimX = dimX;
	volume.dimY = dimY;
	volume.dimZ = dimZ;
	volume.iso = iso;
	volume.data.resize(dimX * dimY * dimZ);
	volume.data = raw;

	// Array of vertices for the extracted surface
	std::vector<dualmc::Vertex> vertices;

	// Array of quad indices for the extracted surface
	std::vector<dualmc::Quad> quads;

	// Compute surface
	computeSurface(volume, vertices, quads);

	// Get vertices
	for (auto const & v : vertices) {
		glm::vec3 vertex;
		vertex.x = v.x;
		vertex.y = v.y;
		vertex.z = v.z;
		objVertices.push_back(vertex);
	}

	// Get quad indices
	for (auto const & q : quads) {
		unsigned int face[4];
		face[0] = q.i0;
		face[1] = q.i1;
		face[2] = q.i2;
		face[3] = q.i3;
		objFaces.push_back(face[0]);
		objFaces.push_back(face[1]);
		objFaces.push_back(face[2]);

		objFaces.push_back(face[0]);
		objFaces.push_back(face[2]);
		objFaces.push_back(face[3]);
	}

}

void dcmToModel::computeSurface(
	Volume volume,
	std::vector<dualmc::Vertex> &vertices,
	std::vector<dualmc::Quad> &quads
) {
	printf("%s" ,"Computing surface...\n");
	dualmc builder;
	builder.build(
		&volume.data.front(),
		volume.dimX,
		volume.dimY,
		volume.dimZ,
		volume.iso * std::numeric_limits<uint8_t>::max(),
		vertices,
		quads
	);
	printf("%s", "Computing surface done.\n");
}