#ifndef __CALLBACKS_H_
#define __CALLBACKS_H_

#include <GLFW/glfw3.h>
#include <stdio.h>

void glfw_callback_input(GLFWwindow *window, int key, int scancode,
		int action, int mods) {
	scancode = 0;
	mods = 0;
	if(scancode || mods) {
		return;
	}

	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}

#endif
