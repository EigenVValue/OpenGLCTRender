// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; 

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "controlsForFOV.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
// Model Matrix; constant
glm::vec3 modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 modelRotation = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 modelScaling = glm::vec3(0.03f, 0.03f, 0.03f);

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
glm::vec3 getModelScaling() {
	return modelScaling;
}

// Initial position & up:

// Initial horizontal angle : none
float horizontalAngle = 0.0f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float mouseSpeed = 0.005f;
bool click = false;

double xpos, ypos;
double currXpos, currYpos;


void computeMatricesFromInputs(
	const int WIDTH, const int HEIGHT,
	glm::vec4 &position, glm::vec4 & up,
	glm::mat4 &rotx, glm::mat4 &roty
) {
	//glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);

	// Rotate
	if (click) {
		// Get mouse position
		glfwGetCursorPos(window, &currXpos, &currYpos);
		// Compute new orientation
		horizontalAngle =mouseSpeed * float(xpos - currXpos);
		verticalAngle = -mouseSpeed * float(ypos - currYpos);
		xpos = currXpos;
		ypos = currYpos;

		// Rotate model
		// Rotate at X-aixs
		//modelRotation.x = verticalAngle;
		// Rotate at Y-aixs
		//modelRotation.y = horizontalAngle;

		// Rotate postion, do what you like
		
		// Rotate at Y-aixs
		glm::mat4 rotationY = glm::mat4(1.0f);
		rotationY[0][0] = glm::cos(horizontalAngle);
		rotationY[0][2] = glm::sin(horizontalAngle);
		rotationY[2][0] = -1 * glm::sin(horizontalAngle);
		rotationY[2][2] = glm::cos(horizontalAngle);

		position = rotx * roty *  rotationY * glm::transpose(roty) * glm::transpose(rotx) * position;
		up = rotx * roty *  rotationY * glm::transpose(roty) * glm::transpose(rotx) * up;
		rotx = rotationY * rotx;

		// Rotate at X-aixs
		glm::mat4 rotationX = glm::mat4(1.0f);
		rotationX[1][1] = glm::cos(verticalAngle);
		rotationX[1][2] = -1 * glm::sin(verticalAngle);
		rotationX[2][1] = glm::sin(verticalAngle);
		rotationX[2][2] = glm::cos(verticalAngle);

		position = roty * rotx * rotationX * glm::transpose(rotx) * glm::transpose(roty) * position;
		up = roty * rotx * rotationX * glm::transpose(rotx) * glm::transpose(roty) * up;
		roty = rotationX * roty;
	}

	// Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(45.0f), float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		glm::vec3(position.x, position.y, position.z),	// Camera is here
		glm::vec3(0, 0, 0),											// Looks at origin(0,0,0)
		glm::vec3(up.x, up.y, up.z)								// Head is up (set to 0,-1,0 to look upside-down)
	);
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		click = true;
		glfwGetCursorPos(window, &xpos, &ypos);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		click = false;
		xpos = NULL;
		ypos = NULL;
	}
}
//void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
//	// Scale the coordinate of position
//	position.x *= 1 - yoffset * 0.05;
//	position.y *= 1 - yoffset * 0.05;
//	position.z *= 1 - yoffset * 0.05;
//}