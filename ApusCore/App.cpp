#include <string>

#include "App.h"



void ApusCore::App::Init() {
	Start();

	time = glfwGetTime();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (!window.ShouldClose()) {
		lastTime = time;
		time = glfwGetTime();
		delta = time - lastTime;
		Tick();
		camera.BindFBO(window.viewportWidth, window.viewportHeight);
		renderer.Render(window.GetProjection(), camera.GetMatrix());
		camera.Render(window.width, window.height);
		window.Update();
		LateTick();
	}

	End();

	renderer.Destroy();
	window.Destroy();
	glfwTerminate();
}

void ApusCore::App::Start() {
	std::cout << "App started" << std::endl;
}

void ApusCore::App::Tick() {
	window.RenameWindow(std::to_string(1 / delta).c_str());
}

void ApusCore::App::LateTick() {
	std::cout << "LateTick" << std::endl;
}

void ApusCore::App::End() {
	std::cout << "App closed" << std::endl;
}

void ApusCore::App::AddObject(Empty* newObject) {
	renderer.sprites.push_back(newObject);
}