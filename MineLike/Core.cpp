#include "Core.h"

GLFWwindow* mainWindow;

GLFWwindow* Core::getMainWindow()
{
	return mainWindow;
}

int Core::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	mainWindow = glfwCreateWindow(800, 600, "NAME", nullptr, nullptr);
	if (mainWindow == nullptr) {
		printf("Failed to create window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mainWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW\n");
		return -1;
	}
	glfwSetKeyCallback(mainWindow, Input::key_callback);
	glfwSetCursorPosCallback(mainWindow, Input::mouse_callback);
	glfwSetScrollCallback(mainWindow, Input::scroll_callback);

	int width, height;
	glfwGetFramebufferSize(mainWindow, &width, &height);

	glViewport(0, 0, width, height);

	//glEnable(GL_STENCIL_TEST);
	//glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glAlphaFunc(GL_GREATER, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//glDisable(GL_CULL_FACE);

	Time::initTime();

	return 0;
}

void mainCycle() {}