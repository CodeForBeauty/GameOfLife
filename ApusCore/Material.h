#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Texture.h"


namespace ApusCore {
	class Material {
	private:
		Shader vs, fs;
		unsigned int program;

		void _Compile();
	public:
		Texture tex;
		Material(): vs("shaders/vertex.vert", GL_VERTEX_SHADER), fs("shaders/fragment.frag", GL_FRAGMENT_SHADER), tex("shaders/Default.jpg") {
			_Compile();
		}
		Material(const char* vertex, const char* pixel = "shaders/fragment.frag", const char* texture = "shaders/Default.jpg") :
			vs(vertex, GL_VERTEX_SHADER), fs(pixel, GL_FRAGMENT_SHADER), tex(texture) {
			_Compile();
		}

		void LoadTexture(const char* path);

		void Destroy();

		void Bind();
	};
}