// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; 
// The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "controls.hpp"
#include <iostream>

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
// Initial position :
glm::vec3 modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 modelRotation = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 modelScale = glm::vec3(1.0f, 1.0f, 1.0f);


glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}
glm::vec3 getModelPosition() {
	return modelPosition;
}
glm::vec3 getModelRotation() {
	return modelRotation;
}
glm::vec3 getModelScale() {
	return modelScale;
}

// Initial horizontal angle : 
float horizontalAngle = 0.01f;
// Initial vertical angle : none
float verticalAngle = 0.01f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.0005f;
bool click = false;

void computeMatricesFromInputs(const int WIDTH,
		const int HEIGHT) {

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);

	// modelRotation
	if (click) {
		// Compute new orientation
		horizontalAngle -= mouseSpeed * float(WIDTH / 2 - xpos);
		verticalAngle -= mouseSpeed * float(HEIGHT / 2 - ypos);
		modelRotation = glm::vec3(3.14159f / 2.0f * verticalAngle, 3.14159f / 2.0f * horizontalAngle, 0);
	}
	
	/*
	// No need for this for now.
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		modelPosition += glm::vec3(0, 0,1) * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		modelPosition -= glm::vec3(0, 0, 1) * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		modelPosition += glm::vec3(1, 0, 0) * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		modelPosition -= glm::vec3(1, 0, 0) * deltaTime * speed;
	}
	*/

	// Projection matrix : Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(initialFoV), float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		glm::vec3(10,10,10),           // Camera is here
		glm::vec3(0,0,0), // and looks here : at the same position, plus "direction"
		glm::vec3(0,1,0)                // Head is up (set to 0,-1,0 to look upside-down)
	);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		click = true;
	} else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		click = false;
	}
}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	modelScale += yoffset*0.05;
}