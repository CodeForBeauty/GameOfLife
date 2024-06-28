#pragma once
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <list>

#include "Sprite.h"
#include "Window.h"
#include "Types.h"


namespace ApusCore {
	class Renderer {
	private:
		Window* window;
	public:
		lm::vec4 background = { 0, 0, 0, 1 };
		std::vector<Empty*> sprites;

		Renderer(Window* window) : window(window) {
			if (!glfwInit())
				throw std::exception("Error: initializing glfw");
		}

		void Init() {
			gladLoadGL();
		}

		void Destroy();

		void Render(lm::mat4 proj, lm::mat4 cam);

		void SetBackground(float x, float y, float z, float w);

		void SaveRender(const char* outputPath, ImageType imgType);
	};
}