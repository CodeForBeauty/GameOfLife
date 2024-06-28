#pragma once
#include <vector>
#include <functional>

#include <lm/lm.h>

#include "Vertex.h"
#include "Material.h"
#include "Window.h"


namespace ApusCore {
	class Empty {
	public:
		virtual void Draw(lm::mat4 proj, lm::mat4 cam) {};
		virtual void Destroy() {};
	};

	class Mesh : public Empty {
	protected:
		std::vector<Vertex> vertices;
		unsigned int vbo, vao;
	public:
		Material material = {};

		Mesh(size_t vertCount);

		void LoadTexture(const char* path);

		virtual void BeforeDraw() { };

		virtual void Destroy() override;
		virtual void Draw(lm::mat4 proj, lm::mat4 cam) override;
		Vertex* GetData();
	};

	class Sprite : public Mesh {
	protected:
		lm::vec4 tintColor;
		lm::vec2 tiling;

		lm::vec2 position;
		lm::vec2 scale;
		float rotation;
		float z;

	public:
		Sprite(lm::vec4 tint = { 1, 1, 1, 1 }, lm::vec2 scale = { 1, 1 }, lm::vec2 position = { 0, 0 }, float rotation = 0, lm::vec2 tiling = { 1, 1 }, const char* texturePath = "shaders/Default.jpg");


		void SetPosition(lm::vec2 newPos);
		void SetRotation(float newRot);
		void SetScale(lm::vec2 scale);

		lm::vec2 GetPosition();
		float GetRotation();
		lm::vec2 GetScale();

		lm::vec2 Move(lm::vec2 offset);
		float Rotate(float offset);
		lm::vec2 Scale(lm::vec2 offset);


		void SetZ(float zValue);
		float GetZ();


		void GenerateTexture(std::function<Color (lm::vec2 pos, lm::vec2 uv)> func, int width, int height, bool hasAlpha);
		void RegenerateTexture(std::function<Color (lm::vec2 pos, lm::vec2 uv, Color previous)> func);
	};

	class ScreenOverlay : public Mesh {
	protected:
		Window* window;
		int lastWidth, lastHeight;

	public:

		ScreenOverlay(Window* window);

		void GenerateTexture(std::function<Color(lm::vec2 pos, lm::vec2 uv)> func, bool hasAlpha);
		void GenerateTexture(std::function<Color(lm::vec2 pos, lm::vec2 uv)> func, int width, int height, bool hasAlpha);
		void RegenerateTexture(std::function<Color(lm::vec2 pos, lm::vec2 uv, Color previous)> func);
	};
}