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

std::vector<glm::vec3> getVertexNormals(
	const std::vector<glm::vec3> &vertices
) {
	std::vector<glm::vec3> normals;
	for (int i = 0; i < vertices.size(); i ++)
	{
		glm::vec3 normal;
		glm::vec3 triangle;
		std::vector<glm::vec3> triangles;
		for (int j = newMinus(i,30); j < newAdd(i,30,vertices.size()-2); j+=3) {
			if (vertices.at(i) == vertices.at(j)
					|| vertices.at(i) == vertices.at(j+1)
					|| vertices.at(i) == vertices.at(j+2)){
				triangle += getNormal(vertices.at(j),vertices.at(j+1), vertices.at(j+2));
				//triangles.push_back(triangle);
			}  else{
				continue;
			}
		}

		//triangle = triangles.at(0);
		//for (int j = 1; j < triangles.size(); j++)
		//{
		//	triangle += triangles.at(j);
		//}

		normal = glm::normalize(triangle);
		normals.push_back(normal);
	}
	return normals;
}

int newMinus(int a, int b) {
	if (a-b < 0)
	{
		return 0;
	}
	else
	{
		return a - b;
	}
}

int newAdd(int a, int b, int c) {
	if (a + b > c)
	{
		return c;
	}
	else
	{
		return a + b;
	}
}