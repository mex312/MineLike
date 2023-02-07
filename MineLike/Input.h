#pragma once
#include "CoreMath.h"

namespace Core
{
	namespace Input
	{
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

		fvec2 getMouseInput();
		bool getKey(i32 key);
		bool getKeyDown(i32 key);

		void updateInput();
		void initInput();
	}
}