#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


namespace ApusCore {

	class Shader {
	private:
		std::string text;
		unsigned int type;
	public:
		unsigned int id;
		Shader(std::string filepath, unsigned int shaderType) : type(shaderType) {
			gladLoadGL();
			LoadFromFile(filepath);
			RecompileShader();
		}

		void Destroy();

		void LoadFromFile(std::string filepath);
		std::string GetShader();
		void SetShader(std::string shader);

		void RecompileShader();
	};
}