#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Camera.h"

namespace ApusCore {
	class App {
	private:
		double lastTime = 0;
	protected:
		Window window;
		Renderer renderer;
		Camera camera;
	public:
		double time = 0, delta = 0;

		App() : window(Window()), renderer(Renderer(&window)), camera(Camera(lm::vec2(), 0)) {
			renderer.Init();
		}

		void Init();

		virtual void Start();
		virtual void Tick();
		virtual void LateTick();
		virtual void End();

		void AddObject(Empty* newObject);
	};
}