#include <vector>

#include <glm/glm.hpp>

#include "getNormals.hpp"

// Get surface normal vector.
std::vector<glm::vec3> getNormals(
	const std::vector<glm::vec3> &vertices)
{
	std::vector<glm::vec3> normals;
	// Start at 3 points which is one triangle.
	for (int i = 0; i < vertices.size(); i+=3)
	{
		glm::vec3 normal = getNormal(vertices.at(i),
			vertices.at(i + 1), vertices.at(i + 2));

		// Let the normal be every point of this triangle.
		normals.push_back(normal);
		normals.push_back(normal);
		normals.push_back(normal);
	}
	return normals;
}

 glm::vec3 getNormal(const glm::vec3 &vertex1,
	const glm::vec3 &vertex2, const glm::vec3 &vertex3)
{
	glm::vec3 normal;
	// U = p2 - p1
	// V = p3 - p1
	// N = U X V
	glm::vec3 vecU = vertex1 - vertex2;
	glm::vec3 vecV = vertex1 - vertex3;
	normal = glm::cross(vecU, vecV);
	

	return normal;
}

std::vector<glm::vec3> getVertexNormals(
	const std::vector<glm::vec3> &vertices)
{
	// Use a lazy threshold to speed up processing.
	// Start at 0 OR the order which is 12 order before the target point.
	// End at last triangle OR the order which is 12 order after the target point.
	// Then check if there exsits any point that equals to target point.
	// If exsits, add up.
	// At last, normalize it.
	std::vector<glm::vec3> normals;
	for (int i = 0; i < vertices.size(); i ++)
	{
		glm::vec3 normal;
		glm::vec3 triangle = glm::vec3(0,0,0);

		// Start lazy check
		for (int j = newMinus(3*(i/3),300); j < newAdd(3 * (i/3),300,vertices.size()); j+=3) {
			if (vertices.at(i) == vertices.at(j)
					|| vertices.at(i) == vertices.at(j+1)
					|| vertices.at(i) == vertices.at(j+2)) {
				triangle += getNormal(vertices.at(j), vertices.at(j + 1), vertices.at(j + 2));
									//* getArea(vertices.at(j), vertices.at(j + 1), vertices.at(j + 2));
			} else{
				continue;
			}
		}
		normal = glm::normalize(triangle);
		
		normals.push_back(normal);
	}
	return normals;
}

int newMinus(int a, int b) {
	if (a-b < 0) {
		return 0;
	} else {
		return a - b;
	}
}
int newAdd(int a, int b, int c) {
	if (a + b > c) {
		return c;
	} else {
		return a + b;
	}
}

// Use Heron's formula to calculate
// area of triangle
float getArea(glm::vec3 vec1, glm::vec3 vec2, glm::vec3 vec3) {
	// Heron's formula:
	// L = (a+b+c)/2
	// S = sqr(L*(L-a)*(L-b)*(L-c)

	float len1 = glm::length(vec1-vec2);
	float len2 = glm::length(vec2-vec3);
	float len3 = glm::length(vec1-vec3);
	float l = len1 + len2 + len3;
	l /= 2;
	float s = glm::sqrt(l*(l - len1)*(l - len2)*(l - len3));

	return s;
}