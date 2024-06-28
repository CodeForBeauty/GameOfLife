#include <iostream>
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <lm/lm.h>


void ApusCore::Window::_windowInit() {
	if (!glfwInit())
		throw std::exception("Error: initializing glfw");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	monitor = glfwGetPrimaryMonitor();
	if (isFullScreen)
		window = glfwCreateWindow(width, height, "App", monitor, NULL);
	else
		window = glfwCreateWindow(width, height, "App", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw std::exception("Error: window wasn't created.");
	}
	glfwMakeContextCurrent(window);
}

void ApusCore::Window::ResizeViewport(int newWidth, int newHeight) {
	viewportWidth = newWidth;
	viewportHeight = newHeight;
	viewportSet = true;
}

void ApusCore::Window::UpdateViewport() {
	glfwGetWindowSize(window, &width, &height);
	viewportWidth = width;
	viewportHeight = height;
}

void ApusCore::Window::RenameWindow(const char* newTitle) {
	glfwSetWindowTitle(window, newTitle);
}

void ApusCore::Window::SetFullscreen(bool newVal) {
	isFullScreen = newVal;
	monitor = glfwGetWindowMonitor(window);
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (newVal)
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	else
		glfwSetWindowMonitor(window, NULL, 0, 0, width, height, mode->refreshRate);
}

bool ApusCore::Window::ToggleFullscreen() {
	isFullScreen = !isFullScreen;
	SetFullscreen(isFullScreen);
	return isFullScreen;
}

int ApusCore::Window::ShouldClose() {
	return glfwWindowShouldClose(window);
}

void ApusCore::Window::Update() {
	glfwGetWindowSize(window, &width, &height);
	if (!viewportSet) {
		viewportWidth = width;
		viewportHeight = height;
	}
	glViewport(0, 0, viewportWidth, viewportHeight);


	glfwSwapBuffers(window);
	glfwPollEvents();
}

lm::mat4 ApusCore::Window::GetProjection() {
	return lm::orthographic(viewportWidth / (float)viewportHeight, 1, 1.0f, -1.0f);
}

void ApusCore::Window::AutoResize(bool newVal) {
	viewportSet = !newVal;
}


