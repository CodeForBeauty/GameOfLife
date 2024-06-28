#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <lm/lm.h>

#include "Shader.h"
#include "Vertex.h"


namespace ApusCore {
	class Camera {
	private:
		Vertex rect[6] = {{ {-1.0f,  1.0f, 0.0f}, {0, 1}, {1, 1, 1, 1} },
							{ { 1.0f, 1.0f, 0.0f }, { 1, 1 }, { 1, 1, 1, 1 } },
							{ { 1.0f, -1.0f, 0.0f }, { 1, 0 }, { 0, 0, 0, 1 } },

							{ { 1.0f, -1.0f, 0.0f }, { 1, 0 }, { 0, 0, 0, 1 } },
							{ { -1.0f, -1.0f, 0.0f }, { 0, 0 }, { 0, 0, 0, 1 } },
							{ { -1.0f, 1.0f, 0.0f }, { 0, 1 }, { 1, 1, 1, 1 } }
		};

		lm::mat4 matrix;
		lm::vec2 position;
		float rotation;

		void UpdateMatrix();

		unsigned int posFBO, posTex, program, vao, vbo;
		Shader vs, fs;
		float lastWidth, lastHeight;
	public:
		Camera(lm::vec2 position, float rotation);
		~Camera();

		lm::vec2 GetPostion() const { return position; }
		float GetRotation() const { return rotation; }

		void SetPosition(lm::vec2 newPosition);
		void SetRotation(float newRotation);
		void Move(lm::vec2 offset);
		void Rotate(float offset);

		lm::mat4 GetMatrix() const { return matrix; }

		void GenerateTexture(float width, float height);
		void BindFBO(float width, float height);

		void Render(float width, float height);
	};
}