#ifndef GETNORMALS_HPP
#define GETNORMALS_HPP

std::vector<glm::vec3> getNormals(
	const std::vector<glm::vec3> &vertices
);

glm::vec3 getNormal(const glm::vec3 &vertex1,
	const glm::vec3 &vertex2, const glm::vec3 &vertex3
);

#endif