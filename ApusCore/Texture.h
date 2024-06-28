#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stb/stb_image.h>

#include <iostream>
#include <functional>

#include "lm/lm.h"
#include "Types.h"


namespace ApusCore {
	class Texture {
	private:
		std::string path;
		unsigned int id;
	protected:
		void UpdateData();
	public:
		unsigned char* data;
		int width, height, channels;

		Texture(const char* path);
		Texture(std::function<Color(lm::vec2 pos, lm::vec2 uv)> func, int width, int height, bool hasAlpha);

		void LoadTexture(const char* texturePath);

		void Clear() {
			glClearTexImage(id, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}

		void Bind() {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void Unbind() {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Generate(std::function<Color (lm::vec2 pos, lm::vec2 uv)> func, bool hasAlpha);

		void Regenerate(std::function<Color(lm::vec2 pos, lm::vec2 uv, Color previous)> func);

		void Save(const char* path, ImageType imgType);

		Color GetPixel(int x, int y);
		void SetPixel(int x, int y, Color value);
	};
}