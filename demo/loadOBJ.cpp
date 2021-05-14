#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>

#include <glm/glm.hpp>

#include "loadOBJ.hpp"

/**
 * OBJ loader
 * Only vertices and their indices, no noramls and UVs.
 * Because obj export from fiji only has its vertices and faces.
 */
bool loadOBJ(const char* path, std::vector<glm::vec3> & out_vertices) {
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices;
	std::vector<glm::vec3> temp_vertices;

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ?\n");
		getchar();
		return false;
	}

	while (1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			// Read line which header is v
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		} else if (strcmp(lineHeader, "f") == 0) {
			// Read line which header is f
			std::string vertex;
			unsigned int vertexIndex[3];
			int matches = fscanf(file, "%ld %ld %ld\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
			if (matches != 3) {
				printf("File can't be read by our simple parser\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
		} else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	} // Loop ends

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
	}

	fclose(file);
	printf("End Loading...\n");
	return true;
}
