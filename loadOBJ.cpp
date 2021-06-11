#include <vector>
#include <stdio.h>
#include <iostream>

#include <glm/glm.hpp>

#include "loadOBJ.hpp"

/**
 * OBJ loader
 * Only vertices and their indices, no noramls and UVs.
 * Because obj export from fiji only has its vertices and faces.
 */

bool loadOBJ(const char* path, std::vector<glm::vec3> & objVertices,
	std::vector<unsigned int> & objFaces) 
{
	printf("Loading OBJ file %s...\n", path);

	FILE * file;
	fopen_s(&file, path, "r");
	if (file == NULL) {
		printf("%s could not be opened. Are you in the right directory ? \n", path); getchar();
		return false;
	}

	while (1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%c", &lineHeader);
		if (res == EOF)
			break;
		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			// Read line which header is v
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			objVertices.push_back(vertex);
		} else if (strcmp(lineHeader, "f") == 0) {
			// Read line which header is f
			unsigned int face[4];
			int matches = fscanf_s(file, "%ld %ld %ld %ld\n", &face[0], &face[1], &face[2], &face[3]);
			if (matches != 4) {
				printf("File can't be read by our simple parser\n");
				fclose(file);
				return false;
			}
			objFaces.push_back(face[0]);
			objFaces.push_back(face[1]);
			objFaces.push_back(face[2]);
			objFaces.push_back(face[3]);
		} else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	} // Loop ends
	
	fclose(file);
	printf("End Loading...\n");
	return true;
}

void objVerticesToGLVertices(std::vector<glm::vec3> & out_vertices,
	const std::vector<glm::vec3> & objVertices,
	const std::vector<unsigned int> & objFaces) {

	// For each vertex of each triangle
	for (unsigned int i = 0; i < objFaces.size(); i+=4) {

		// Get the indices of its attributes
		// Get the attributes thanks to the index
		glm::vec3 vertex;

		vertex = objVertices[objFaces[i] - 1];
		out_vertices.push_back(vertex);
		vertex = objVertices[objFaces[i+3] - 1];
		out_vertices.push_back(vertex);
		vertex = objVertices[objFaces[i+2] - 1];
		out_vertices.push_back(vertex);
		vertex = objVertices[objFaces[i+3] - 1];
		out_vertices.push_back(vertex);
		vertex = objVertices[objFaces[i+2] - 1];
		out_vertices.push_back(vertex);
		vertex = objVertices[objFaces[i+1] - 1];
		out_vertices.push_back(vertex);
	}

	// Get pivot
	float pivot[3] = { 0.0f };
	for (auto & vertex : out_vertices) {
		// Add up
		pivot[0] += vertex.x;
		pivot[1] += vertex.y;
		pivot[2] += vertex.z;
	}
	pivot[0] /= out_vertices.size();
	pivot[1] /= out_vertices.size();
	pivot[2] /= out_vertices.size();

	for (auto & vertex : out_vertices) {
		vertex.x -= pivot[0];
		vertex.y -= pivot[1];
		vertex.z -= pivot[2];
	}
}