#ifndef CONTROLSFORFOV_HPP
#define CONTROLSFORFOV_HPP

void computeMatricesFromInputs(
	const int WIDTH, const int HEIGHT,
	glm::vec4 &position, glm::vec4 & up,
	glm::mat4 &x, glm::mat4 &y
);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
glm::vec3 getModelPosition();
glm::vec3 getModelRotation();
glm::vec3 getModelScaling();

void mouse_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

#endif // CONTROLSFORFOV_HPP