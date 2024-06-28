#pragma once
#include <lm/lm.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace ApusCore {
	class Window {
	private:
		GLFWmonitor* monitor;
		GLFWwindow* window;
		bool viewportSet;
	public:
		int width, height, viewportWidth, viewportHeight;
		bool isFullScreen = false;

		Window(int WindowWidth = 850, int WindowHeight = 600, bool fullScreen = false) : 
			width(WindowWidth), height(WindowHeight), isFullScreen(fullScreen), viewportWidth(WindowWidth), viewportHeight(WindowHeight) {
			_windowInit();
		}
		Window(const char* title, int WindowWidth = 850, int WindowHeight = 600, bool fullScreen = false) : 
			width(WindowWidth), height(WindowHeight), isFullScreen(fullScreen), viewportWidth(WindowWidth), viewportHeight(WindowHeight) {
			_windowInit();
		}

		void Destroy() {
			glfwDestroyWindow(window);
		}

		void _windowInit();

		void ResizeViewport(int newWidth, int newHeight);
		void UpdateViewport();
		void RenameWindow(const char* newTitle);
		void SetFullscreen(bool newVal);
		bool ToggleFullscreen();

		int ShouldClose();
		void Update();
		lm::mat4 GetProjection();

		void AutoResize(bool newVal);

		GLFWwindow* GetWindow() {
			return window;
		}
	};
}