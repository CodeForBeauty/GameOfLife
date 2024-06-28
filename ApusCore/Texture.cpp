#include "Texture.h"
#include <iostream>

#include <stb/stb_image_write.h>


void ApusCore::Texture::UpdateData() {
	Bind();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (channels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	Unbind();
}

ApusCore::Texture::Texture(const char* path) : path(path) {
	data = stbi_load(path, &width, &height, &channels, 0);

	glGenTextures(1, &id);
	UpdateData();
}

ApusCore::Texture::Texture(std::function<Color(lm::vec2 pos, lm::vec2 uv)> func, int width, int height, bool hasAlpha) : width(width), height(height) {
	glGenTextures(1, &id);

	Generate(func, hasAlpha);
}

void ApusCore::Texture::LoadTexture(const char* texturePath) {
	if (strcmp(path.c_str(), texturePath) == 0)
		return;
	Clear();
	path = texturePath;
	data = stbi_load(texturePath, &width, &height, &channels, 0);


	UpdateData();
}

void ApusCore::Texture::Generate(std::function<Color (lm::vec2 pos, lm::vec2 uv)> func, bool hasAlpha) {
	Clear();
	channels = hasAlpha ? 4 : 3;
	data = new unsigned char[width * height * channels];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Color pixel = func({ (float)i, (float)j }, { (float)i / (float)width, (float)j / (float)height });

			SetPixel(i, j, pixel);
		}
	}

	UpdateData();
}

void ApusCore::Texture::Regenerate(std::function<Color(lm::vec2 pos, lm::vec2 uv, Color previous)> func) {
	if (channels < 3 || width == 0 || height == 0)
		return;
	unsigned char* newData = new unsigned char[width * height * channels];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Color previous = GetPixel(i, j);
			if (channels == 4)
				previous.a = (float)data[(i + width * j) * channels + 3] / 255.0f;
			Color pixel = func({ (float)i, (float)j }, { (float)i / width, (float)j / height }, previous);

			pixel = pixel * 255;
			unsigned char* offset = newData + (i + width * j) * channels;
			offset[0] = (unsigned char)pixel.r;
			offset[1] = (unsigned char)pixel.g;
			offset[2] = (unsigned char)pixel.b;
			if (channels > 3)
				offset[3] = (unsigned char)pixel.a;
		}
	}

	Clear();
	data = newData;
	UpdateData();
}

void ApusCore::Texture::Save(const char* outputPath, ApusCore::ImageType imgType) {
	switch (imgType) {
	case ApusCore::png:
		stbi_write_png(outputPath, width, height, 3, data, width * 3);
		break;
	case ApusCore::jpeg:
		stbi_write_jpg(outputPath, width, height, 3, data, width * 3);
		break;
	case ApusCore::bmp:
		stbi_write_bmp(outputPath, width, height, 3, data);
		break;
	case ApusCore::tga:
		stbi_write_tga(outputPath, width, height, 3, data);
		break;
	}
}

ApusCore::Color ApusCore::Texture::GetPixel(int x, int y) {
	unsigned char* offset = data + (x + width * y) * channels;
	Color output = {
				(float)offset[0] / 255.0f,
				(float)offset[1] / 255.0f,
				(float)offset[2] / 255.0f
	};
	if (channels == 4)
		output.a = (float)offset[3] / 255.0f;
	return output;
}

void ApusCore::Texture::SetPixel(int x, int y, Color value) {
	value = value * 255;
	unsigned char* offset = data + (x + width * y) * channels;
	offset[0] = (unsigned char)value.r;
	offset[1] = (unsigned char)value.g;
	offset[2] = (unsigned char)value.b;
	if (channels > 3)
		offset[3] = (unsigned char)value.a;
}
