#ifndef GETUVS_HPP
#define GETUVS_HPP

void getUVs(
	const std::vector<glm::vec3> & vertices,
	const std::vector<int> & colors,
	std::vector<glm::vec2> & uvs
);

#endif // GETUVS_HPP