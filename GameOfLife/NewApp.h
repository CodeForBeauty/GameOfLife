#pragma once
#include <App.h>
#include <Sprite.h>

#include <cmath>


class NewApp : public ApusCore::App {
public:
	ApusCore::ScreenOverlay canvas = ApusCore::ScreenOverlay(&window);

	int width, height;
	double tickThreashold = 1.0f / 10.0f;
	double timeFromLastTick = 0;

	bool* tiles;
	bool* tiles1;
	GLFWwindow* win;

	bool placing = true;

	bool pressed = false;

	void Start() override {
		win = window.GetWindow();

		std::cout << "Enter canvas width: ";
		std::cin >> width;
		std::cout << "Enter canvas height: ";
		std::cin >> height;

		auto generator = [](lm::vec2 pos, lm::vec2 uv) {
			ApusCore::Color output = { uv.x, uv.y, 0, 1 };
			return output;
		};

		tiles = new bool[width * height];
		tiles1 = new bool[width * height];
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				tiles[i + width * j] = false;
			}
		}
		window.ResizeViewport(width, height);
		glfwSetWindowAspectRatio(win, width, height);
		canvas.GenerateTexture(generator, true);

		AddObject(&canvas);

	}

	int CountNeightbours(int x, int y) {
		int count = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (i == 0 && j == 0) {
					continue;
				}
				int posx = x + i, posy = y + j;
				if (posx < 0 || posy < 0 || posx >= width || posy >= height) {
					continue;
				}
				count += (int)tiles[posx + width * posy];
			}
		}
		return count;
	}

	void Tick() override {
		timeFromLastTick += delta;
		if (timeFromLastTick < tickThreashold) {
			return;
		}
		timeFromLastTick = 0;

		if (!placing) {
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					int neighbours = CountNeightbours(i, j);
					if (tiles[i + width * j]) {
						if (neighbours < 2 || neighbours > 3) {
							tiles1[i + width * j] = false;
						}
						else {
							tiles1[i + width * j] = true;
						}
					}
					else {
						if (neighbours == 3) {
							tiles1[i + width * j] = true;
						}
						else {
							tiles1[i + width * j] = false;
						}
					}
				}
			}

			bool* tmp = tiles;
			tiles = tiles1;
			tiles1 = tmp;
		}

		auto generator = [this](lm::vec2 pos, lm::vec2 uv, ApusCore::Color prev) {
			float val = 1;//CountNeightbours(pos.x, pos.y);
			ApusCore::Color output = { val, val, val, val };
			return output * tiles[(int)(pos.x + width * pos.y)];
		};

		canvas.RegenerateTexture(generator);
	}

	void SetValueWithMouse(bool value) {
		double mouseX, mouseY;
		glfwGetCursorPos(win, &mouseX, &mouseY);
		if (mouseX < 0 || mouseY < 0 || mouseX >= window.width || mouseY >= window.height) {
			return;
		}
		mouseY = window.height - mouseY;
		int x = mouseX / window.width * width;
		int y = mouseY / window.height * height;
		tiles[x + width * y] = value;
	}

	void LateTick() override {
		if (glfwGetKey(win, GLFW_KEY_P)) {
			if (!pressed) {
				placing = !placing;
				pressed = true;
			}
		}
		else {
			pressed = false;
		}
		if (placing && glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT)) {
			SetValueWithMouse(true);
		}
		if (placing && glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_RIGHT)) {
			SetValueWithMouse(false);
		}
	}

	void End() override {
		delete[] tiles;
	}
};