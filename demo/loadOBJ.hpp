#ifndef LOADOBJ_HPP
#define LOADOBJ_HPP

bool loadOBJ(
	const char * path,
	std::vector<glm::vec3> & objVertices,
	std::vector<unsigned int> & objFaces
);

void objVerticesToGLVertices(
	std::vector<glm::vec3> & out_vertices,
	const std::vector<glm::vec3> & objVertices,
	const std::vector<unsigned int> & objFaces);

#endif