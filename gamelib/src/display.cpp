#include "stdafx.h"
#include <GL/glew.h>
#include "display.h"
#include <stdexcept>

Display::Display(int w, int h, bool fullscreen) : _screenWidth(w), _screenHeight(h) {

}

Display::~Display() {}

GLFWDisplay::~GLFWDisplay() {
	glfwTerminate();
}

GLFWDisplay::GLFWDisplay(int w, int h, bool fullscreen) : Display(w, h, fullscreen) {
	if (!glfwInit()) {
		throw std::runtime_error("failed to init GLFW");
	}

	GLFWmonitor* mon = nullptr;
	if (fullscreen) mon = glfwGetPrimaryMonitor();

	_window = glfwCreateWindow(w, h, "Game", mon, nullptr);
	if (!_window) {
		glfwTerminate();
		throw std::runtime_error("failed to init GLFW window");
	}

	glfwMakeContextCurrent(_window);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		throw std::runtime_error("failed to init GLEW");
	}

}

void GLFWDisplay::swapBuffers() {
	glfwSwapBuffers(_window);
}

void GLFWDisplay::pollEvents() {
	glfwPollEvents();
}