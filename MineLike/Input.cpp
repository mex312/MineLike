#include "Input.h"

using namespace Core;

static float mouseSensitivity = 1.0f;
static float scrollSensitivity = 1.0f;


bool keysDown[1024];
bool keysActual[1024];
std::set<int> keysToPress;
std::set<int> keysToUnPress;

bool keys[1024];
void Core::Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (action == GLFW_PRESS) {
		keys[key] = true;
		if(!keysDown[key])
			keysToPress.insert(key);
	}
	else if (action == GLFW_RELEASE) {
		keys[key] = false;
		keysToUnPress.insert(key);
	}
}

fvec2 lastMousePos(0);
fvec2 nowMousePos(0);
fvec2 deltaMousePos(0);
bool mouseMoved = false;
void Core::Input::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!mouseMoved) {
		lastMousePos = glm::vec2(xpos, ypos);
		mouseMoved = true;
	}
	nowMousePos = glm::vec2(xpos, ypos);
}

fvec2 nowScroll(0);
fvec2 deltaScroll(0);
void Core::Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	nowScroll += glm::vec2(xoffset, yoffset);
}

void Core::Input::updateInput()
{
	deltaMousePos = (nowMousePos - lastMousePos) * mouseSensitivity;
	lastMousePos = nowMousePos;

	deltaScroll = nowScroll * scrollSensitivity;
	nowScroll = glm::vec2(0);

	for (int i = 0; i < 1024; i++)
	{
		if (keysDown[i]) keysActual[i] = false;
	}
	for (int k : keysToPress)
	{
		keysDown[k] = true;
		keysActual[k] = true;
	}
	for (int k : keysToUnPress)
	{
		keysDown[k] = false;
		keysActual[k] = false;
	}

	keysToPress.clear();
	keysToUnPress.clear();
}

void Core::Input::initInput()
{
	for (int i = 0; i < 1024; i++)
	{
		keys[i] = false;
		keysDown[i] = false;
		keysActual[i] = false;
	}

	mouseSensitivity = 1.0f;
	scrollSensitivity = 1.0f;
}

fvec2 Core::Input::getMouseInput()
{
	return deltaMousePos;
}

bool Core::Input::getKeyDown(i32 key)
{
	return keysActual[key];
}

bool Core::Input::getKey(i32 key)
{
	return keys[key];
}