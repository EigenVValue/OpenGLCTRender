#ifndef GETNORMALS_HPP
#define GETNORMALS_HPP

std::vector<glm::vec3> getNormals(
	const std::vector<glm::vec3> &vertices
);

glm::vec3 getNormal(const glm::vec3 &vertex1,
	const glm::vec3 &vertex2, const glm::vec3 &vertex3
);

std::vector<glm::vec3> getVertexNormals(
	const std::vector<glm::vec3> &vertices
);

int newMinus(int a, int b);
int newAdd(int a, int b, int c);

float getArea(glm::vec3 vec1, glm::vec3 vec2, glm::vec3 vec3);

#endif