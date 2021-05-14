#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs(const int WIDTH,
	const int HEIGHT);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
glm::vec3 getPosition();

#endif