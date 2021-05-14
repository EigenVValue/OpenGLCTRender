#include <vector>

// Include GLM
#include <glm/glm.hpp>

#include "getNormals.hpp"

std::vector<glm::vec3> getNormals(
	const std::vector<glm::vec3> &vertices
) {
	std::vector<glm::vec3> normals;
	// Start at 3 points which is one triangle
	for (int i = 0; i < vertices.size(); i+=3)
	{
		glm::vec3 normal = getNormal(vertices.at(i),
			vertices.at(i + 1), vertices.at(i + 2));

		normals.push_back(normal);
		normals.push_back(normal);
		normals.push_back(normal);
	}
	return normals;
}

glm::vec3 getNormal(const glm::vec3 &vertex1,
	const glm::vec3 &vertex2, const glm::vec3 &vertex3
) {
	glm::vec3 normal;
	glm::vec3 vecU = vertex2 - vertex1;
	glm::vec3 vecV = vertex3 - vertex1;

	normal = glm::cross(vecU, vecV);

	return normal;
}