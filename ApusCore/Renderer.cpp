#include "Renderer.h"
#include "stb/stb_image_write.h"


#include<iostream>

void ApusCore::Renderer::Destroy() {
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i]->Destroy();
	}
}

void ApusCore::Renderer::Render(lm::mat4 proj, lm::mat4 cam) {
	glClearColor(background.x, background.y, background.z, background.w);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < sprites.size(); i++) {
		sprites[i]->Draw(proj, cam);
	}
}

void ApusCore::Renderer::SetBackground(float x, float y, float z, float w) {
	background = { x, y, z, w };
}

void ApusCore::Renderer::SaveRender(const char* outputPath, ApusCore::ImageType imgType) {
	unsigned char* data = new unsigned char[window->viewportWidth * window->viewportHeight * 3];
	glReadPixels(0, 0, window->viewportWidth, window->viewportHeight, GL_RGB, GL_UNSIGNED_BYTE, data);

	switch (imgType)
	{
	case ApusCore::png:
		stbi_write_png(outputPath, window->viewportWidth, window->viewportHeight, 3, data, window->viewportWidth * 3);
		break;
	case ApusCore::jpeg:
		stbi_write_jpg(outputPath, window->viewportWidth, window->viewportHeight, 3, data, window->viewportWidth * 3);
		break;
	case ApusCore::bmp:
		stbi_write_bmp(outputPath, window->viewportWidth, window->viewportHeight, 3, data);
		break;
	case ApusCore::tga:
		stbi_write_tga(outputPath, window->viewportWidth, window->viewportHeight, 3, data);
		break;
	}

	delete[] data;
}
